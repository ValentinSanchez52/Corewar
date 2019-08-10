/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 04:44:37 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/08 14:19:28 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Applies bitwise operator (xor/^) between the first and the second arg
**	Stores it into the register given (third arg)
*/

void				op_xor(t_process *proc)
{
	uint32_t		value_1;
	uint32_t		value_2;

	if (proc->op.types[0] == COR_ARG_REG)
		value_1 = get_reg_value(proc, proc->op.args[0]);
	else if (proc->op.types[0] == COR_ARG_DIR)
		value_1 = proc->op.args[0];
	else if (proc->op.types[0] == COR_ARG_IND)
		value_1 = get_mem_value(proc->global_offset + proc->pc
				+ ((uint16_t)proc->op.args[0] % COR_IDX_MOD), COR_REG_SIZE);
	if (proc->op.types[1] == COR_ARG_REG)
		value_2 = get_reg_value(proc, proc->op.args[1]);
	else if (proc->op.types[1] == COR_ARG_DIR)
		value_2 = proc->op.args[1];
	else if (proc->op.types[1] == COR_ARG_IND)
		value_2 = get_mem_value(proc->global_offset + proc->pc
				+ ((uint16_t)proc->op.args[1] % COR_IDX_MOD), COR_REG_SIZE);
	reg_set_value(proc, proc->op.args[2], value_1 ^ value_2);
	proc->carry = (!get_reg_value(proc, proc->op.args[2]));
}
