/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction_from_arena.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:05:18 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/26 06:59:57 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "parsing.h"

inline t_op				get_instruction_from_arena(
		t_process *process,
		uint32_t memory
)
{
	uint32_t			args[COR_ARG_NUMBER_MAX];
	t_op_arg_code		types[COR_ARG_NUMBER_MAX];
	t_op_check			properties;
	uint8_t				encode;
	uint32_t			i;

	encode = get_mem_cell(memory + 1);
	properties = g_op_check[get_mem_cell(memory)];
	i = UINT32_MAX;
	if (!properties.encoding)
	{
		while (++i < properties.count)
			args[i] = get_arg_value(memory, properties.default_types, i);
		types[0] = properties.default_types[0];
		types[1] = properties.default_types[1];
		types[2] = properties.default_types[2];
		types[3] = properties.default_types[3];
	}
	else
		while (++i < properties.count)
		{
			types[i] = ((get_arg_type(encode, i)) >> 1) + 1;
			args[i] = get_arg_value(memory, types, i);
		}
	return ((t_op){
			.code = get_mem_cell(memory), .param_count = properties.count,
			.timeout = properties.cycles, .process = process,
			.types = {types[0], types[1], types[2], types[3]},
			.args = {args[0], args[1], args[2], args[3]},
	});
}
