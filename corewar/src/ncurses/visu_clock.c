/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_clock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:50:57 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 16:02:00 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_clock(void)
{
	static uint8_t	index;

	mvprintw(VISU_ARENA_TB + 2, VISU_VS + 4 ,
			"[--------------------------------------------------]");
	mvprintw(VISU_ARENA_TB + 2, VISU_VS + 5 + index , "o");
	index = (index + 1) % 50;
}
