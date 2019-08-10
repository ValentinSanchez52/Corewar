/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 07:12:31 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/08 14:21:35 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				op_lld(t_process *proc)
{
	uint32_t		value;
	uint32_t		reg_id;

	reg_id = proc->op.args[1];
	if (proc->op.types[0] == COR_ARG_IND)
	{
		value = (proc->pc + (uint16_t)proc->op.args[0]);
		reg_set_value(proc, reg_id, get_mem_value(value, COR_REG_SIZE));
	}
	else if (proc->op.types[0] == COR_ARG_DIR)
		reg_set_value(proc, reg_id, proc->op.args[0]);
	proc->carry = (!get_reg_value(proc, proc->op.args[0]));
}
