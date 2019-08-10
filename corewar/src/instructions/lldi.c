/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 07:17:31 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/10 18:42:16 by vsanchez         ###   ########.fr       */
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

void				op_lldi(t_process *proc)
{
	uint32_t		value_1;
	uint32_t		value_2;
	uint8_t			reg_id;

	if (!((reg_id = proc->op.args[2]) && reg_id <= 16))
		return ;
	if (proc->op.types[0] == COR_ARG_REG && proc->op.args[0]
			&& proc->op.args[0] <= 16)
		value_1 = get_reg_value(proc, proc->op.args[0]);
	else if (!(value_1 = get_value(proc, 0)))
		return ;
	if (proc->op.types[1] == COR_ARG_REG && proc->op.args[1]
			&& proc->op.args[1] <= 16)
		value_2 = get_reg_value(proc, proc->op.args[1]);
	else if (proc->op.types[1] == COR_ARG_DIR)
		value_2 = (uint16_t)proc->op.args[1];
	else
		return ;
	reg_set_value(proc, reg_id, get_mem_value(proc->global_offset + proc->pc
				+ (int16_t)(value_1 + value_2), COR_REG_SIZE));
}
