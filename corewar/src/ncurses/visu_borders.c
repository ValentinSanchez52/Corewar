/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_borders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:43:09 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 19:26:31 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_borders(void)
{
	int			x;
	int			y;

	x = VISU_LEFT_B - 1;
	y = VISU_TOP_B - 1;
	attron(COLOR_PAIR(5));
	while (++x <= VISU_RIGHT_B)
		mvprintw(y + 1, x, "*");
	while (++y <= VISU_BOT_B)
		mvprintw(y, x - 1, "*");
	while (--x >= VISU_LEFT_B)
		mvprintw(y - 1, x, "*");
	while (--y >= VISU_TOP_B)
		mvprintw(y, x + 1, "*");
	while (++y <= VISU_BOT_B)
		mvprintw(y, VISU_VS, "*");
	mvprintw(VISU_HEADER, VISU_VS + 1, "*");
	mvprintw(VISU_HEADER, VISU_RIGHT_B - 1, "*");
	mvprintw(VISU_WARRIOR, VISU_VS + 1, "*");
	mvprintw(VISU_WARRIOR, VISU_RIGHT_B - 1, "*");
	attroff(COLOR_PAIR(5));
}
