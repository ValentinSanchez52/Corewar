/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:05:50 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 19:08:48 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Generic help function
*/

t_bboa_state			help(t_arg_array *args)
{
	return (BBOA_RS_DISPLAY_USAGE);
}

t_bboa_state			set_dump(t_arg_array *args)
{
	if (args->len < 1 || args->array[0].type != BBOA_AT_INTEGER)
		return (BBOA_RS_NOT_ENOUGH_ARGS);
	g_vm.flags.dump_cycle = (uint32_t)args->array[0].integer_token.number;
	g_vm.flags.dump = true;
	return (BBOA_RS_OK);
}

t_bboa_state			set_vm_debug(t_arg_array *args)
{
	g_vm.flags.debug = true;
	return (BBOA_RS_OK);
}

t_bboa_state			set_dump_size(t_arg_array *args)
{
	uint32_t				arg;

	if (args->len < 1)
		return (BBOA_RS_NOT_ENOUGH_ARGS);
	if (args->array[0].type != BBOA_AT_INTEGER)
		return (BBOA_RS_TYPE_MISMATCH);
	arg = (uint32_t)args->array[0].integer_token.number;
	if (arg == 64)
		g_vm.flags.dump_size = DMP_SIZE_64;
	else if (arg == 128)
		g_vm.flags.dump_size = DMP_SIZE_128;
	else if (arg != 32)
		return (BBOA_RS_INVALID_ARG);
	return (BBOA_RS_OK);
}

t_bboa_state			parse_player(t_arg_array *args)
{
	if (args->len < 2)
		return (BBOA_RS_NOT_ENOUGH_ARGS);
	else if (args->array[0].type != BBOA_AT_INTEGER
			|| args->array[0].integer_token.invalid
			|| args->array[1].type != BBOA_AT_STRING
			|| args->array[0].integer_token.number > 4
			|| !args->array[0].integer_token.number)
		return (BBOA_RS_TYPE_MISMATCH);
	corewar_load_warriors(args->array[0].integer_token.number - 1,
			args->array[1].string_token.string);
	return (BBOA_RS_OK);
}
