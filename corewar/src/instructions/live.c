/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:42:21 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/19 19:47:00 by vsanchez         ###   ########.fr       */
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
		if (g_vm.warriors[warrior_i].id == id)
		{
			g_vm.warriors[warrior_i].cycle_last = g_vm.cycles;
			g_vm.warriors[warrior_i].period_lives++;
			g_vm.warriors[warrior_i].living = 1;
			break ;
		}
		warrior_i++;
	}
}

void				op_live(t_process *proc)
{
	proc->living = true;
	warrior_live(proc->op.args[0]);
	g_vm.live_counter++;
}
