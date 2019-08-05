/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:06:18 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/05 20:55:11 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Loads to a register (second arg) a value given (first arg)
*/

void				op_ld(t_op *op)
{
	uint32_t		value;
	uint32_t		reg_id;

	reg_id = op->args[1];
	if (op->types[0] == COR_ARG_IND)
	{
		value = op->process->global_offset + op->process->pc
			+ ((uint16_t)op->args[0] % COR_IDX_MOD);
		reg_set_value(op->process, reg_id, get_mem_value(value, COR_REG_SIZE));
		op->process->carry = (!get_reg_value(op->process, op->args[0]));
	}
	else if (op->types[0] == COR_ARG_DIR)
	{
		reg_set_value(op->process, reg_id, op->args[0]);
	}
}
