/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:42:21 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/25 17:05:57 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	warrior_live(uint32_t id)
{
	uint8_t			warrior_i;

	warrior_i = 0;
	while (warrior_i < COR_WARRIOR_NB_MAX)
		if (vm.warriors[warrior_i].id == id)
		{
			vm.warriors[warrior_i].cycle_last = vm.cycles;
			vm.warriors[warrior_i].living = 1;
			break ;
		}
}

void				live(t_op *op)
{
	op->process->living = 1;
	warrior_live(op->args[0]);
	vm.live_counter++;
}
