/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 04:31:26 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 07:44:44 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				op_sub(t_op *op)
{
	reg_set_value(op->process, op->args[2],
			get_reg_value(op->process, op->args[0])
			- get_reg_value(op->process, op->args[1]));
	op->process->carry = (!get_reg_value(op->process, op->args[2]));
}
