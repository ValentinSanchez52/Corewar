/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 05:10:09 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/19 20:00:42 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Pastes register given into memory address given by args 2 & 3
*/

void				op_sti(t_process *proc)
{
	uint32_t				value_1;
	uint32_t				value_2;
	uint8_t					reg_id;

	if (!(proc->op.types[0] == COR_ARG_REG && (reg_id = proc->op.args[0])
			&& proc->op.args[0] <= 16))
		return ;
	if (proc->op.types[1] == COR_ARG_REG && proc->op.args[1]
			&& proc->op.args[1] <= 16)
		value_1 = get_reg_value(proc, proc->op.args[1]);
	else if (proc->op.types[1] == COR_ARG_DIR)
		value_1 = (uint16_t)proc->op.args[1];
	else if (proc->op.types[1] == COR_ARG_IND)
		value_1 = get_mem_value(proc->global_offset + proc->pc
				+ ((uint16_t)proc->op.args[1] % COR_IDX_MOD), COR_REG_SIZE);
	if (proc->op.types[2] == COR_ARG_REG && proc->op.args[2]
			&& proc->op.args[2] <= 16)
		value_2 = get_reg_value(proc, proc->op.args[2]);
	else if (proc->op.types[2] == COR_ARG_DIR)
		value_2 = (uint16_t)proc->op.args[2];
	set_mem_value(proc->global_offset + proc->pc
			+ (int16_t)(value_1 + value_2) % COR_IDX_MOD,
			get_reg_value(proc, reg_id), COR_REG_SIZE,
			get_cell_claim(proc->global_offset + proc->pc));
}
