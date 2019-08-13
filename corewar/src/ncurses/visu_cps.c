/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_cps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:41:28 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 15:42:56 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_cps(void)
{
	mvprintw(VISU_ARENA_TB + 4, (VISU_VS + VISU_RIGHT_B) / 2 - 13 ,
			"Cycles per second max:     ");
	mvprintw(VISU_ARENA_TB + 4, (VISU_VS + VISU_RIGHT_B) / 2 + 10 ,
			ft_ultostr(g_vm.visu.speed, 10, 0));
}
