/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:44:40 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/19 19:04:52 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_state(void)
{
	if (g_vm.visu.state == VISU_RUNNING)
		mvprintw(VISU_ARENA_TB, VISU_INFO_MID - 3, "RUNNING");
	else
		mvprintw(VISU_ARENA_TB, VISU_INFO_MID - 3, "PAUSED ");
}
