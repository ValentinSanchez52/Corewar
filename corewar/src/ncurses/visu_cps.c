/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_cps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:41:28 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/16 05:33:04 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_cps(void)
{
	mvprintw(VISU_ARENA_TB + 4, VISU_INFOS, "Cycles per second max <        ");
	if (g_vm.visu.speed < VISU_CPS_MAX)
		mvprintw(VISU_ARENA_TB + 4, VISU_INFOS + 24,
				ft_ultostr(g_vm.visu.speed, 10, 0));
	else
		mvprintw(VISU_ARENA_TB + 4, VISU_INFOS + 22, "unlimited");
}
