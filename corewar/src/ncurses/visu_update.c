/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:34:50 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/14 17:13:13 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_update(void)
{
	while (g_vm.visu.state == VISU_PAUSED)
		g_vm.visu.state = visu_get_key();
	g_vm.visu.state = visu_get_key();
	visu_arena();
	visu_processes();
	visu_clock();
	visu_live();
	visu_debug();
	refresh();
	cps_max();
}
