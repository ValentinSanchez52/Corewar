/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:08:52 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/05 21:06:57 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "parsing.h"

inline uint32_t			get_instruction_size(
		t_op *op
)
{
	t_op_check			properties;
	uint32_t			size;
	uint32_t			i;

	properties = g_op_check[op->code];
	size = 1 + properties.encoding;
	i = 0;
	while (i < op->param_count)
	{
		if (properties.dir_addr && op->types[i] == COR_ARG_DIR)
			size += 2;
		else
			size += g_op_arg_code_size[op->types[i]];
		i++;
	}
	return (size);
}
