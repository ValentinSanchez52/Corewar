/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:28:47 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 16:39:21 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				start_visu(void)
{
	WINDOW				*win;

	initscr();	//To init visu
	timeout(0);	//To set getch as key_interrupt
	noecho();	//To suppress the automatic echoing of typed characters
	curs_set(0);	//To have no cursor
	start_color();	//To start colors
	init_pair(1, COLOR_GREEN, COLOR_BLACK);		//Colors
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);		//BORDER COLOR
	init_pair(6, COLOR_WHITE, COLOR_BLACK);		//default
	win = newwin(NLINES + 1, NCOLS, 0, 0);	//To set a new window

	g_vm.visu.speed = 1;
	g_vm.visu.state = VISU_PAUSED;
	visu_legend();
	visu_borders();
	visu_cps();
	visu_update();
}
