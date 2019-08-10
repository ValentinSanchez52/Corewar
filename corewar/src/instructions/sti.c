/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 05:10:09 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/10 19:15:09 by vsanchez         ###   ########.fr       */
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
**	Pastes register given into memory address given by args 2 & 3
*/

void				op_sti(t_process *proc)
{
	uint32_t		value_1;
	uint32_t		value_2;

	if (proc->op.types[1] == COR_ARG_REG && proc->op.args[1]
			&& proc->op.args[1] <= 16)
		value_1 = get_reg_value(proc, proc->op.args[1]);
	else if (!(value_1 = get_value(proc, 1)))
		return ;
	if (proc->op.types[2] == COR_ARG_REG && proc->op.args[1]
			&& proc->op.args[1] <= 16)
		value_2 = get_reg_value(proc, proc->op.args[2]);
	else if (proc->op.types[2] == COR_ARG_DIR)
		value_2 = (uint16_t)proc->op.args[2];
	else
		return ;
	set_mem_value(proc->global_offset + proc->pc
			+ (int16_t)(value_1 + value_2) % COR_IDX_MOD,
			get_reg_value(proc, proc->op.args[0]), COR_REG_SIZE,
			get_cell_claim(proc->global_offset + proc->pc));
}
