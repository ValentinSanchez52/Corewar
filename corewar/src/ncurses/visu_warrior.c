/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_warrior.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 19:11:17 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/14 17:44:32 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void				visu_warrior(void)
{
	uint8_t			warrior_id;

	mvprintw(VISU_WARRIOR, VISU_INFOS,
			"[-------------------- WARRIORS ----------------------]");
	warrior_id = 0;
	while (warrior_id < COR_WARRIOR_NB_MAX)
	{
		if (g_vm.warriors[warrior_id].id)
		{
			mvprintw(VISU_WARRIOR + 2 + ((1 + VISU_NB_WINFO) * warrior_id),
					VISU_INFOS, "Warrior  :");
			mvprintw(VISU_WARRIOR + 2 + ((1 + VISU_NB_WINFO) * warrior_id),
					VISU_INFOS + 8, ft_ultostr(warrior_id + 1, 10, 0));
			attron(COLOR_PAIR(warrior_id + 1));
			mvprintw(VISU_WARRIOR + 2 + ((1 + VISU_NB_WINFO) * warrior_id),
					VISU_INFOS + 13, g_vm.warriors[warrior_id].name);
			attroff(COLOR_PAIR(warrior_id + 1));
			visu_live();
		}
		warrior_id++;
	}
}
