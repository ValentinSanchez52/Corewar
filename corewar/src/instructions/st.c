/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:23:41 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/08 16:45:58 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Store data from a register to an arena mem 4 bytes cell or to a register
*/

void				op_st(t_process *proc)
{
	uint32_t		reg_id;
	uint32_t		reg_2_id;

	if (proc->op.types[1] == COR_ARG_REG)
	{
		reg_set_value(proc, proc->op.args[1],
				get_reg_value(proc, proc->op.args[0]));
	}
	else if (proc->op.types[1] == COR_ARG_IND)
		set_mem_value(proc->global_offset + proc->pc
				+ (uint16_t)proc->op.args[1] % COR_IDX_MOD,
				get_reg_value(proc, proc->op.args[0]), sizeof(t_reg));
}
