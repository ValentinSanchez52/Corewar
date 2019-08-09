/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 04:45:45 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/09 15:12:52 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Makes pc move to a memory cell no longer than COR_IDX_MOD
*/

void				op_zjmp(t_process *proc)
{
	/*printf("Process: global_offset %d, pc %d", proc->global_offset, proc->pc);*/
	if (proc->carry && proc->op.args[0])
		proc->pc += ((int16_t)proc->op.args[0] % COR_IDX_MOD);
	else
		proc->pc += 3;
	/*printf(" --------> proc_pc %d\n", proc->pc);*/
}
