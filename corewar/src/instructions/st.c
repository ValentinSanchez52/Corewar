/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:23:41 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 11:55:02 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Store data from a register to an arena mem 4 bytes cell or to a register
*/

void				op_st(t_op *op)
{
	uint32_t		reg_id;
	uint32_t		reg_2_id;

	if (op->types[1] == COR_ARG_REG)
	{
		reg_set_value(op->process, op->args[1],
				get_reg_value(op->process, op->args[0]));
	}
	else if (op->types[1] == COR_ARG_IND)
		set_mem_value(op->process->global_offset + op->process->pc
				+ (uint16_t)op->args[1] % COR_IDX_MOD,
				get_reg_value(op->process, op->args[0]),
				COR_ARG_SIZ_REG);
}
