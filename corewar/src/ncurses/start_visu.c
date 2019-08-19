/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:28:47 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/19 18:05:11 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

t_bboa_state			load_visu(t_arg_array *args)
{
	g_vm.visu.used = true;
	return (BBOA_RS_OK);
}

/*
**	initscr();	//To init visu
**	timeout(0);	//To set getch as key_interrupt
**	noecho();	//To suppress the automatic echoing of typed characters
**	curs_set(0);	//To have no cursor
**	start_color();	//To start colors
**	init_pair(1, COLOR_GREEN, COLOR_BLACK);		//Colors
**	init_pair(2, COLOR_BLUE, COLOR_BLACK);
**	init_pair(3, COLOR_RED, COLOR_BLACK);
**	init_pair(4, COLOR_CYAN, COLOR_BLACK);
**	init_pair(5, COLOR_WHITE, COLOR_WHITE);		//BORDER COLOR
**	init_pair(6, COLOR_WHITE, COLOR_BLACK);		//default
**	g_vm.visu.win = newwin(VISU_HEIGHT, VISU_WIDTH, 0, 0);	//To set new window
*/

inline void				start_visu(void)
{
	initscr();
	timeout(0);
	noecho();
	curs_set(0);
	start_color();
	init_pair(VISU_CLR_W1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(VISU_CLR_W2, COLOR_BLUE, COLOR_BLACK);
	init_pair(VISU_CLR_W3, COLOR_RED, COLOR_BLACK);
	init_pair(VISU_CLR_W4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_WHITE, COLOR_BLACK);
	g_vm.visu.win = newwin(VISU_HEIGHT, VISU_WIDTH, 0, 0);
	g_vm.visu.speed = 1;
	g_vm.visu.state = VISU_PAUSED;
	visu_borders();
	visu_legend();
	visu_debug();
	visu_warrior();
	visu_cps();
	visu_clock();
	visu_arena();
	visu_processes();
	refresh();
}
