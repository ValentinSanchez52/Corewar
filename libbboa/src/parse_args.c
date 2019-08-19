/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:36:18 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 20:44:42 by mbeilles         ###   ########.fr       */
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

t_opt_patterns		**mtch(void)
{
	static t_opt_patterns	*matches;

	return (&matches);
}

/*
**	Generates an array of tokens that corresponds to the arguments in order.
**		If there is not the right number of argument left, it's padded by
**		nulls.
**	The implementation of exiting if the number of arguments doesn't match
**	is left to the writter of the callback function.
*/

t_arg_array			*generate_tokens(
		t_opt_match *match,
		char *opt,
		uint32_t args_left,
		t_arg_gen gen
)
{
	static t_convert_function	matrix[BBOA_AT_MAX_TYPE] = {
		[BBOA_AT_NONE] = &bboa_parse_void,
		[BBOA_AT_STRING] = &bboa_parse_string,
		[BBOA_AT_DOUBLE] = &bboa_parse_double,
		[BBOA_AT_INTEGER] = &bboa_parse_integer,
		[BBOA_AT_BOOLEAN] = &bboa_parse_boolean,
	};
	t_arg_array					*tkn;

	if (!(tkn = (t_arg_array*)malloc(sizeof(t_arg_array)))
			|| !(tkn->array = (t_arg_token*)malloc(sizeof(t_arg_token)
					* match->arg_count)))
		return (NULL);
	tkn->len = ~0u;
	tkn->opt = ft_strdup(opt);
	tkn->data = (*mtch())->data;
	tkn->opt_len = ft_strlen(opt);
	if (gen.first && match->arg_count > 0)
		tkn->array[++tkn->len] = matrix[match->types[tkn->len]](gen.first);
	while (++tkn->len < match->arg_count && tkn->len - !!gen.first < args_left
			&& gen.args[tkn->len - !!gen.first])
		tkn->array[tkn->len] = matrix[match->types[tkn->len]](gen.args[tkn->len
				- !!gen.first]);
	return (tkn);
}

static inline int	bboa_find_terminator(
		char **argv,
		int argc,
		char *terminator
)
{
	int				i;

	i = 0;
	while (i < argc)
	{
		if (ft_strequ(argv[i], terminator))
			return (i);
		++i;
	}
	return (argc);
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
**	-rwla=[arg4] [arg0] [arg1] [arg2] [arg3] -- not args
**
**	Assuming that each option only takes 1 argument except `a` which takes 2.
*/

char				**bboa_parse_args(t_opt_patterns *options
									, int argc, char **argv)
{
	t_bboa_parse_args	a;

	a = (t_bboa_parse_args){.arg = 0, .st = BBOA_RS_OK, .last_args = argv};
	*mtch() = options;
	argc = bboa_find_terminator(argv, argc, "--");
	while (a.arg < argc && a.st == BBOA_RS_OK)
	{
		if (bboa_is_double(argv[a.arg]) && (a.last_args = argv + a.arg + 1))
			a.st = parse_double_arg(&a.last_args, a.arg, argc, argv + a.arg);
		else if (bboa_is_single(argv[a.arg]) && (a.last_args = argv + a.arg + 1)
				&& (a.st = parse_long_single_arg(&a.last_args,
						a.arg, argc, argv + a.arg))
				== BBOA_RS_UNKNOWN_OPT)
			a.st = parse_single_arg(&a.last_args, a.arg, argc, argv + a.arg);
		if (a.arg >= a.last_args - argv)
			a.arg++;
		else
			a.arg = a.last_args - argv;
	}
	if (a.st <= BBOA_RS_OK)
		return (a.last_args);
	bboa_set_error_usage(*mtch(), argv[0] + 1 + (argv[0][1] == '-'), a.st,
			(g_bboa_error.level) ? BBOA_EC : g_bboa_error.level);
	bboa_print_error(g_bboa_error);
	return (NULL);
}
