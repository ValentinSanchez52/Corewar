/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 04:45:45 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 12:18:00 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Makes pc move to a memory cell no longer than COR_IDX_MOD
*/

void				op_zjmp(t_op *op)
{
	if (op->process->carry)
		op->process->pc += ((uint16_t)op->args[0] % COR_IDX_MOD);
}
