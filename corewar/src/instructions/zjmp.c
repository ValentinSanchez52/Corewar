/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 04:45:45 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/05 18:54:24 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Makes pc move to a memory cell no longer than COR_IDX_MOD
*/

void				op_zjmp(t_op *op)
{
	if (op->process->carry)
		op->process->pc = (op->process->pc + op->args[0])
			& (COR_ARENA_SIZE - 1);
}
