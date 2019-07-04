/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:36:18 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/04 19:44:10 by mbeilles         ###   ########.fr       */
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

t_opt_patterns			**mtch(void)
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

t_arg_array				*generate_tokens(
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
	*tkn = (t_arg_array){
			.array = tkn->array, .len = ~0u,
			.opt = ft_strdup(opt), .opt_len = ft_strlen(opt),
			.data = (*mtch())->data
	};
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
			if ((st = parse_long_single_arg(&last_args, arg, argc, argv + arg))
					== BBOA_RS_UNKNOWN_OPT)
				st = parse_single_arg(&last_args, arg, argc, argv + arg);
	}
	if (st <= BBOA_RS_OK)
		return (last_args);
	bboa_set_error_usage(*mtch(), ft_strrchr(argv[0], '-') + 1, st, BBOA_EC);
	bboa_print_error(g_bboa_error);
	return (NULL);
}
