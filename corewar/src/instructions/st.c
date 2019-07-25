/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:23:41 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/25 19:32:29 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				st(t_op *op)
{
	uint32_t		reg_id;
	uint32_t		reg_2_id;

	reg_id = op->args[0];
	if (op->types[1] == COR_ARG_REG)
	{
		reg_2_id = op->args[1];
		reg_set_value(op->process, reg_2_id,
				get_reg_value(op->process, reg_id));
	}
	else if (op->types[1] == COR_ARG_IND)
		reg_set_value(op->process, reg_2_id, op->args[1]);
}
