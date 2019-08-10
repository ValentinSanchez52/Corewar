/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:18:59 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/05 17:36:53 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "parsing.h"

inline uint32_t			get_arg_value(
		uint32_t memory,
		t_op_arg_code *types,
		uint32_t index
)
{
	t_op_arg_code		code;
	uint32_t			i;
	uint32_t			j;
	uint32_t			len;

	code = get_mem_cell(memory);
	i = 0;
	j = 1 + g_op_check[code].encoding;
	while (i < index)
	{
		if (g_op_check[code].dir_addr && types[i] == COR_ARG_DIR)
			j += 2;
		else
			j += g_op_arg_code_size[types[i]];
		++i;
	}
	if (g_op_check[code].dir_addr && types[i] == COR_ARG_DIR)
		len = 2;
	else
		len = g_op_arg_code_size[types[i]];
	return (get_mem_value(memory + j, len));
}
