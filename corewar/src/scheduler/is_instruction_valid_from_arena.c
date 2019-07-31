/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_instruction_valid_from_arena.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:09:40 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/26 10:40:15 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "parsing.h"

inline bool				is_instruction_valid_from_arena(
		uint32_t memory
)
{
	uint8_t				encode;
	uint8_t				i;
	uint8_t				cell;

	cell = get_mem_cell(memory);
	if (cell == 0 || cell >= COR_OP_MAX)
		return (false);
	if (g_op_check[cell].encoding)
	{
		encode = get_mem_cell(memory + 1);
		i = 0xff;
		while (++i < g_op_check[cell].count)
			if (!((1 << (get_arg_type(encode, i) - 1))
						& g_op_check[cell].args[i]))
				return (false);
	}
	/* printf("Valid\n"); */
	return (true);
}
