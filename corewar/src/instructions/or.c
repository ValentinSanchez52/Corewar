/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 04:42:35 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/19 19:48:22 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static uint32_t		get_value(t_process *proc, uint8_t arg)
{
	uint32_t		value;

	value = 0;
	if (proc->op.types[arg] == COR_ARG_DIR)
		value = proc->op.args[arg];
	else if (proc->op.types[arg] == COR_ARG_IND)
		value = get_mem_value(proc->global_offset + proc->pc
				+ ((uint16_t)proc->op.args[arg] % COR_IDX_MOD), COR_REG_SIZE);
	return (value);
}

/*
**	Applies bitwise operator (or/|) between the first and the second arg
**	Stores it into the register given (third arg)
*/

void				op_or(t_process *proc)
{
	uint32_t		value_1;
	uint32_t		value_2;
	uint8_t			reg_id;

	if (!((reg_id = proc->op.args[2]) && reg_id <= 16))
		return ;
	if (proc->op.types[0] == COR_ARG_REG && proc->op.args[0]
			&& proc->op.args[0] <= 16)
		value_1 = get_reg_value(proc, proc->op.args[0]);
	else
		value_1 = get_value(proc, 0);
	if (proc->op.types[1] == COR_ARG_REG && proc->op.args[1]
			&& proc->op.args[1] <= 16)
		value_2 = get_reg_value(proc, proc->op.args[1]);
	else
		value_2 = get_value(proc, 1);
	reg_set_value(proc, reg_id, value_1 | value_2);
	proc->carry = (!get_reg_value(proc, reg_id));
}
