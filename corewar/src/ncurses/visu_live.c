/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:12:09 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/14 19:24:30 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static inline void	visu_warrior_state(uint8_t warrior_id)
{
	if (g_vm.warriors[warrior_id].living)
	{
		attron(COLOR_PAIR(VISU_GREEN));
		mvprintw(VISU_WARRIOR + 4 + ((1 + VISU_NB_WINFO) * warrior_id),
				VISU_INFOS, "Alive");
		attroff(COLOR_PAIR(VISU_GREEN));
	}
	else
	{
		attron(COLOR_PAIR(VISU_RED));
		mvprintw(VISU_WARRIOR + 4 + ((1 + VISU_NB_WINFO) * warrior_id),
				VISU_INFOS, "Dying");
		attroff(COLOR_PAIR(VISU_RED));
	}
}

void				visu_live(void)
{
	uint8_t			warrior_id;

	warrior_id = 0;
	while (warrior_id < COR_WARRIOR_NB_MAX)
	{
		if (g_vm.warriors[warrior_id].id)
		{
			mvprintw(VISU_WARRIOR + 3 + ((1 + VISU_NB_WINFO) * warrior_id),
					VISU_INFOS, "Last live:       ");
			mvprintw(VISU_WARRIOR + 3 + ((1 + VISU_NB_WINFO) * warrior_id),
					VISU_INFOS + 11,
					ft_ultostr(g_vm.warriors[warrior_id].cycle_last, 10, 0));
			visu_warrior_state(warrior_id);
		}
		warrior_id++;
	}
}
