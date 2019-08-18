/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_clock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:50:57 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/18 08:10:27 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_clock(void)
{
	static uint8_t	index;

	mvprintw(VISU_ARENA_TB + 2, VISU_INFOS,
			"[----------------------------------------------------]");
	mvprintw(VISU_ARENA_TB + 2, VISU_INFOS + 1 + index, "o");
	index = (index + 1) % 52;
	if (g_vm.cycles_to_die <= COR_CYCLES_DEFAULT)
	{
		mvprintw(VISU_ARENA_TB + 6, VISU_INFOS, "Current cycle:     ");
		mvprintw(VISU_ARENA_TB + 6, VISU_INFOS + 15,
				ft_ultostr(g_vm.cycles, 10, 0));
		mvprintw(VISU_ARENA_TB + 6, VISU_INFOS + 37, "Cycles left:     ");
		mvprintw(VISU_ARENA_TB + 6, VISU_INFOS + 50,
				ft_ultostr(g_vm.cycles_to_die - g_vm.cycles_counter, 10, 0));
	}
}
