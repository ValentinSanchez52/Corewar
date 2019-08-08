/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:06:18 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/08 17:02:07 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Loads to a register (second arg) a value given (first arg)
*/

void				op_ld(t_process *proc)
{
	uint32_t		value;
	uint32_t		reg_id;
	t_op_arg_code	type;

	if (!((reg_id = proc->op.args[1]) && reg_id <= 16))
		return ;
	type = proc->op.types[0];
	if (type == COR_ARG_IND)
	{
		value = proc->global_offset + proc->pc
			+ ((uint16_t)proc->op.args[0] % COR_IDX_MOD);
		reg_set_value(proc, reg_id, get_mem_value(value, COR_REG_SIZE));
	}
	else if (type == COR_ARG_DIR)
	{
		reg_set_value(proc, reg_id, proc->op.args[0]);
	}
	if (proc->op.args[0] && proc->op.args[0] <= 16)
		proc->carry = (!get_reg_value(proc, proc->op.args[0]));
}
