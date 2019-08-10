/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:23:41 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/10 17:10:20 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Store data from a register to an arena mem 4 bytes cell or to a register
*/

void				op_st(t_process *proc)
{
	uint32_t		reg_id;

	if (!((reg_id = proc->op.args[0]) && reg_id <= 16))
		return ;
	if (proc->op.types[1] == COR_ARG_REG)
	{
		reg_set_value(proc, proc->op.args[1],
				get_reg_value(proc, reg_id));
	}
	else if (proc->op.types[1] == COR_ARG_IND)
		set_mem_value(proc->global_offset + proc->pc
				+ (uint16_t)proc->op.args[1] % COR_IDX_MOD,
				get_reg_value(proc, reg_id), sizeof(t_reg));
}
