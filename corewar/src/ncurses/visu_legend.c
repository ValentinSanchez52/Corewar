/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_legend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:44:06 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 19:33:55 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_legend(void)
{
	mvprintw(VISU_ARENA_BB - 4, VISU_VS + 3, "D:	Decrese speed	    ->	\
     Shift + D: by 10");
	mvprintw(VISU_ARENA_BB - 3, VISU_VS + 3, "I:	Increse speed	    ->	\
     Shift + I: by 10");
	mvprintw(VISU_ARENA_BB - 2, VISU_VS + 3, "Space:	Start/Pause/Continue");
	mvprintw(VISU_ARENA_BB - 1, VISU_VS + 3, "P:	Pause");
	mvprintw(VISU_ARENA_BB, VISU_VS + 3, "Q:	Quit");
}
