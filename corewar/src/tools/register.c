/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:45:02 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/25 18:57:11 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					reg_set_value(t_process *process, uint8_t reg_id,
		uint32_t value)
{
	process->registers[reg_id] = value;
}

uint32_t				get_reg_value(t_process *process, uint8_t reg_id)
{
	return ((process->registers[reg_id]));
}

uint32_t				*get_register(t_process *process, uint8_t reg_id)
{
	return (&(process->registers[reg_id]));
}
