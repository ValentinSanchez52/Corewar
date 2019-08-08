/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 04:45:45 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/08 14:19:44 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Makes pc move to a memory cell no longer than COR_IDX_MOD
*/

void				op_zjmp(t_process *proc)
{
	if (proc->carry)
		proc->pc = (proc->pc + proc->op.args[0])
			& (COR_ARENA_SIZE - 1);
}
