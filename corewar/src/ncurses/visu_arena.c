/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:02:50 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 16:03:02 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_arena(void)
{
	uint16_t		index;
	uint8_t			color_id;

	index = 0;
	while (index < 4096)
	{
		if (!(color_id = get_cell_claim(index)))
			color_id = 6;
		attron(COLOR_PAIR(color_id));
		mvprintw(VISU_ARENA_TB + index / 64, VISU_ARENA_LB + ((index % 64) * 3),
				ft_ultostr(get_mem_cell(index), 16, 0));
		index++;
	}
	attroff(COLOR_PAIR(color_id));
}
