/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:02:50 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/20 13:34:51 by vsanchez         ###   ########.fr       */
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
	bool			bold;

	bold = false;
	index = -1;
	while (++index < 4096)
	{
		if (!(color_id = get_cell_claim(index)) || color_id > COR_ARN_MAX)
			color_id = 6;
		else if (color_id > COR_ARN_W4_CLAIM && (bold = true))
		{
			attron(A_BOLD);
			if (!(color_id = color_id % 4))
				color_id = 4;
			g_vm.arena_claim[index] -= (get_cell_claim(index)
					> COR_ARN_W4_CLAIM ? 4 : 0);
		}
		attron(COLOR_PAIR(color_id));
		mvprintw(VISU_ARENA_TB + index / 64, VISU_ARENA_LB + ((index % 64) * 3),
				cell_format(ft_ultostr(get_mem_cell(index), 16, 0)));
		attroff(COLOR_PAIR(color_id));
		if (bold)
			attroff(A_BOLD);
	}
}
