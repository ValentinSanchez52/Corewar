/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 05:10:09 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 11:17:17 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				op_sti(t_op *op)
{
	uint32_t		value_1;
	uint32_t		value_2;

	if (op->types[1] == COR_ARG_REG)
		value_1 = get_reg_value(op->process, op->args[1]);
	else if (op->types[1] == COR_ARG_DIR)
		value_1 = (uint16_t)op->args[1];
	else if (op->types[1] == COR_ARG_IND)
		value_1 = get_mem_value(op->process->pc
				+ ((uint16_t)op->args[1] % COR_IDX_MOD), COR_REG_SIZE);
	if (op->types[2] == COR_ARG_REG)
		value_2 = get_reg_value(op->process, op->args[2]);
	else if (op->types[2] == COR_ARG_DIR)
		value_2 = (uint16_t)op->args[2];
	set_mem_value(op->process->pc + (value_1 + value_2) % COR_IDX_MOD,
			get_reg_value(op->process, op->args[0]), COR_REG_SIZE);
}
