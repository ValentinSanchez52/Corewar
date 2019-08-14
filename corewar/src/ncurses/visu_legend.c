/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_legend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:44:06 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/14 17:45:25 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_legend(void)
{
	attron(COLOR_PAIR(5));
	mvprintw(VISU_ARENA_BB - 8, VISU_VS,
			"***********************************************************");
	attroff(COLOR_PAIR(5));
	mvprintw(VISU_ARENA_BB - 6, VISU_INFOS,
			"[---------------------- LEGEND ----------------------]");
	mvprintw(VISU_ARENA_BB - 4, VISU_INFOS, "D:	Decrese speed	    ->	\
     Shift + D: by 10");
	mvprintw(VISU_ARENA_BB - 3, VISU_INFOS, "I:	Increse speed	    ->	\
     Shift + I: by 10");
	mvprintw(VISU_ARENA_BB - 2, VISU_INFOS, "Space:	Start/Pause/Continue");
	mvprintw(VISU_ARENA_BB - 1, VISU_INFOS, "P:	Pause");
	mvprintw(VISU_ARENA_BB, VISU_INFOS, "Q:	Quit");
}
