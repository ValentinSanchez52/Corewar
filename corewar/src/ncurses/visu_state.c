/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:44:40 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 19:18:21 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_state(void)
{
	mvprintw(VISU_ARENA_TB, VISU_INFO_MID - 3,
			(g_vm.visu.state ? "RUNNING" : "PAUSED "));
}
