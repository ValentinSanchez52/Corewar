/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:02:50 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/18 13:12:05 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static inline char		*cell_format(char *str)
{
	static char			cell[3];

	cell[0] = '0';
	if (ft_strlen(str) == 1)
		cell[1] = *str;
	if (ft_strlen(str) == 2)
	{
		cell[0] = str[0];
		cell[1] = str[1];
	}
	return (cell);
}

inline void				visu_arena(void)
{
	uint16_t		index;
	uint8_t			color_id;

	index = 0;
	while (index < 4096)
	{
		if (!(color_id = get_cell_claim(index)) || color_id > 6)
			color_id = 6;
		attron(COLOR_PAIR(color_id));
		mvprintw(VISU_ARENA_TB + index / 64, VISU_ARENA_LB + ((index % 64) * 3),
				cell_format(ft_ultostr(get_mem_cell(index), 16, 0)));
		index++;
	}
	attroff(COLOR_PAIR(color_id));
}
