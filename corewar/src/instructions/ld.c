/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:06:18 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/25 19:31:59 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				ld(t_op *op)
{
	uint32_t		value;
	uint32_t		reg_id;

	op->process->carry = (op->args[0] == 0);
	reg_id = op->args[1];
	if (op->types[0] == COR_ARG_IND)
	{
		value = op->process->pc + (op->args[0] % COR_IDX_MOD);
		reg_set_value(op->process, reg_id, get_mem_value(value, COR_REG_SIZE));
	}
	else if (op->types[0] == COR_ARG_DIR)
		reg_set_value(op->process, reg_id, op->args[0]);
}
