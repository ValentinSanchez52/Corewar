/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:06:18 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 07:44:10 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				op_ld(t_op *op)
{
	uint32_t		value;
	uint32_t		reg_id;

	reg_id = op->args[1];
	if (op->types[0] == COR_ARG_IND)
	{
		value = op->process->pc + ((uint16_t)op->args[0] % COR_IDX_MOD);
		reg_set_value(op->process, reg_id, get_mem_value(value, COR_REG_SIZE));
	}
	else if (op->types[0] == COR_ARG_DIR)
		reg_set_value(op->process, reg_id, op->args[0]);
	op->process->carry = (!get_reg_value(op->process, op->args[0]));
}
