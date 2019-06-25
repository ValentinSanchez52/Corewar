/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:36:18 by mbeilles          #+#    #+#             */
/*   Updated: 2019/06/25 14:33:40 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashmap.h"
#include "bboa.h"
#include "libft.h"

/*
**	This is just a singleton for ease of use when using this lib with 42 normed
**		projects.
*/

static t_opt_patterns	**mtch(void)
{
	static t_opt_patterns	*map;

	return (&map);
}

/*
**	Generates an array of tokens that corresponds to the arguments in order.
**		If there is not the right number of argument left, it's padded by
**		nulls.
**	The implementation of exiting if the number of arguments doesn't match
**	is left to the writter of the callback function.
*/

static t_arg_array		*generate_tokens(
		t_opt_match *match,
		char *opt,
		uint32_t args_left,
		t_arg_gen gen
)
{
	static t_convert_function	matrix[BBOA_AT_MAX_TYPE] = {
		[BBOA_AT_NONE] = &bboa_parse_void,
		[BBOA_AT_STRING] = &bboa_parse_string,
		[BBOA_AT_NUMBER] = &bboa_parse_number,
		[BBOA_AT_BOOLEAN] = &bboa_parse_boolean,
	};
	t_arg_array					*tkn;

	if (!(tkn = (t_arg_array*)malloc(sizeof(t_arg_array)))
			|| !(tkn->array = (t_arg_token*)malloc(sizeof(t_arg_token)
					* match->arg_count)))
		return (NULL);
	tkn->len = ~0u;
	tkn->opt = ft_strdup(opt);
	tkn->opt_len = ft_strlen(opt);
	tkn->data = (*mtch())->data;
	if (gen.first && match->arg_count > 0)
		tkn->array[++tkn->len] = matrix[match->types[tkn->len]](gen.first);
	while (++tkn->len < match->arg_count && tkn->len - !!gen.first < args_left
			&& gen.args[tkn->len - !!gen.first]
			&& gen.args[tkn->len - !!gen.first][0] != '-')
		tkn->array[tkn->len] = matrix[match->types[tkn->len]](gen.args[tkn->len
				- !!gen.first]);
	return (tkn);
}

/*
**	| Parse a double dash option and it's arguments |
**		`str` points to the start of what is after '='.
**
**	This function gets of there's is a match for the argument
**		then generate tokens.
**	If the state of return is different of OK it asumes there's an error
**		and prints.
**	Then frees the token and it's content.
*/

static t_bboa_state		parse_double_arg(
		char ***last,
		uint32_t arg,
		int argc,
		char **argv
)
{
	t_opt_match		*match;
	t_arg_array		*tkn;
	char			*str;
	t_bboa_state	state;

	if ((str = ft_strrchr(argv[0] + 2, '=')))
		*str++ = '\0';
	if (ft_hashmap_get((*mtch())->map, (uint8_t*)argv[0] + 2,
				(void**)&match) && match)
	{
		if (!(tkn = generate_tokens(match, argv[0] + 2, argc - arg - 1,
						(t_arg_gen){argv + 1, str})))
			return (BBOA_RS_GENERIC_ERROR);
		*last = (argv + tkn->len + !str > *last)
			? argv + tkn->len + !str : *last;
		if ((state = match->func(tkn)) == BBOA_RS_DISPLAY_USAGE)
			bboa_set_error_usage((*mtch())->map, *argv + 2, state,
					BBOA_ERR_INFO);
		ft_afree(3, tkn->array, tkn->opt, tkn);
		return (state);
	}
	return (BBOA_RS_OK);
}

/*
**	| Parse all single dash options contained in the argument string |
**	For norm purposes the return state is stored at the end of `s`.
**		`str` points to the start of what is after '='.
**
**	This function loops over each char of the arguement until a '=' or the end.
**		for each char it copies to `s` so that it's a string only containing it.
**		then it generate tokens as above.
**	If the state of return is different of OK it asumes there's an error
**		and prints.
**	Then frees the token and it's content.
*/

static t_bboa_state		parse_single_arg(
		char ***lt,
		uint32_t arg,
		int ac,
		char **av
)
{
	t_opt_match		*mth;
	t_arg_array		*tkn;
	static char		s[3] = " \0";
	char			*str;
	uint32_t		i;

	s[2] = (char)BBOA_RS_OK;
	i = 0;
	if ((str = ft_strrchr(av[0] + 2, '=')))
		*str++ = '\0';
	while (s[2] <= BBOA_RS_OK && (s[0] = av[0][++i]))
		if (ft_hashmap_get((*mtch())->map, (uint8_t*)s, (void**)&mth) && mth)
		{
			if (!(tkn = generate_tokens(mth, s, ac - (*lt - av) + !!str,
							(t_arg_gen){.args = *lt, .first = (av[0]
									+ i + 2 == str) ? str : NULL})))
				return (BBOA_RS_GENERIC_ERROR);
			*lt += tkn->len - (av[0] + i + 2 == str);
			if ((s[2] = mth->func(tkn)) == BBOA_RS_DISPLAY_USAGE)
				bboa_set_error_usage((*mtch())->map, s, s[2], BBOA_ERR_INFO);
			ft_afree(3, tkn->array, tkn->opt, tkn);
		}
		else
			return (bboa_set_error_usage((*mtch())->map, s, BBOA_NOT, BBOA_EC));
	return ((t_bboa_state)s[2]);
}

/*
**	Loop through the argv, whatch out this doesn't exclude the first argv.
**		then checks if the argument is:
**		* A double dash option
**		* A single dash option:
**		* A dumb string: These are just skipped but the behavior can be changed.
**		And do the apropriate action.
**		Then display the error message if an error was catched.
**
**	To be noted that double dash are more that one char and simple are one.
**		The advantage of simple dash is that you can nest them in this manner:
**
**	-rwla=[arg4] [arg0] [arg1] [arg2] [arg3]
**
**	Assuming that each option only takes 1 argument except `a` which takes 2.
*/

char					**bboa_parse_args(
		t_opt_patterns *options,
		int argc,
		char **argv
)
{
	uint32_t			arg;
	t_bboa_state		st;
	char				**last_args;

	arg = ~0u;
	st = BBOA_RS_OK;
	last_args = argv;
	*mtch() = options;
	while (last_args - argv < argc && st == BBOA_RS_OK)
	{
		arg = last_args - argv;
		if (argv[arg] && argv[arg][0] == '-' && argv[arg][1] == '-'
				&& (last_args = argv + arg + 1))
			st = parse_double_arg(&last_args, arg, argc, argv + arg);
		else if (argv[arg] && argv[arg][0] == '-'
				&& (last_args = argv + arg + 1))
			st = parse_single_arg(&last_args, arg, argc, argv + arg);
		else
			st = BBOA_RS_NONE;
	}
	if (st <= BBOA_RS_OK)
		return (last_args);
	bboa_print_error(g_bboa_error);
	return (NULL);
}
