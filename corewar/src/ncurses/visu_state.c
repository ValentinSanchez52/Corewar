/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:44:40 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 15:44:55 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_state(void)
{
		mvprintw(VISU_ARENA_TB, (VISU_VS + VISU_RIGHT_B) / 2 - 3,
				(g_vm.visu.state ? "RUNNING" : "PAUSED "));
}
