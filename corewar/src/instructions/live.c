/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:42:21 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 11:43:10 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Live instructions increases live_counter, sets the process to state living
**	sets the warrior alive if id matches and update the last cycle linving for
**	the warrior
*/

static inline void	warrior_live(uint32_t id)
{
	uint8_t			warrior_i;

	warrior_i = 0;
	while (warrior_i < COR_WARRIOR_NB_MAX)
	{
		if (vm.warriors[warrior_i].id == id)
		{
			vm.warriors[warrior_i].cycle_last = vm.cycles;
			vm.warriors[warrior_i].living = 1;
			break ;
		}
		warrior_i++;
	}
}

void				op_live(t_op *op)
{
	op->process->living = 1;
	printf("live_id: %#08x\n", op->args[0]);
	warrior_live(op->args[0]);
	vm.live_counter++;
}
