/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 04:24:34 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/08 14:16:28 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				op_add(t_process *proc)
{
	reg_set_value(proc, proc->op.args[2],
			get_reg_value(proc, proc->op.args[0])
			+ get_reg_value(proc, proc->op.args[1]));
	proc->carry = (!get_reg_value(proc, proc->op.args[2]));
}
