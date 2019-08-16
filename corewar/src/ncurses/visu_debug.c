/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:10:06 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/16 07:15:02 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static inline void		visu_lives_bar(void)
{
	uint8_t				index;

	index = 0;
	attron(COLOR_PAIR(VISU_GREEN));
	attron(A_BOLD);
	while (index < g_vm.live_counter && index < COR_CYCLES_LIVES)
	{
		mvprintw(VISU_DBG_INFO + 0, VISU_INFOS + 6 + index * 2,"--");
		index++;
	}
	attroff(COLOR_PAIR(VISU_GREEN));
	attroff(A_BOLD);
}

inline void				visu_debug(void)
{
	mvprintw(VISU_DBG_INFO - 1, VISU_INFOS,
			"Live counter for current period : ");
	mvprintw(VISU_DBG_INFO + 0, VISU_INFOS + 5,
			"[------------------------------------------]");
	visu_lives_bar();
	mvprintw(VISU_DBG_INFO + 2, VISU_INFOS, "Lives by period:       ");
	mvprintw(VISU_DBG_INFO + 2, VISU_INFOS + 17,
			ft_ultostr(COR_CYCLES_LIVES, 10, 0));
	mvprintw(VISU_DBG_INFO + 4, VISU_INFOS, "Cycle to die:       ");
	mvprintw(VISU_DBG_INFO + 4, VISU_INFOS + 14,
			ft_ultostr(g_vm.cycles_to_die, 10, 0));
	mvprintw(VISU_DBG_INFO + 6, VISU_INFOS, "Cycle delta:       ");
	mvprintw(VISU_DBG_INFO + 6, VISU_INFOS + 13,
			ft_ultostr(COR_CYCLES_DELTA, 10, 0));
	mvprintw(VISU_DBG_INFO + 8, VISU_INFOS, "Last clear:       ");
	mvprintw(VISU_DBG_INFO + 8, VISU_INFOS + 12,
			ft_ultostr(g_vm.last_clear, 10, 0));
	mvprintw(VISU_DBG_INFO + 10, VISU_INFOS, "Current check:       ");
	mvprintw(VISU_DBG_INFO + 10, VISU_INFOS + 15,
			ft_ultostr(COR_CYCLES_LEFT + 1 - g_vm.cycles_left, 10, 0));
	mvprintw(VISU_DBG_INFO + 12, VISU_INFOS, "Process counter:       ");
	mvprintw(VISU_DBG_INFO + 12, VISU_INFOS + 17,
			ft_ultostr(g_vm.process.index / sizeof(t_process), 10, 0));
}
