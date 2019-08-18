/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_get_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:45:29 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/18 09:05:35 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void			visu_get_speed_key(uint32_t key)
{
	if (key == 0x69 && g_vm.visu.speed < VISU_CPS_MAX)
		++g_vm.visu.speed;
	else if (key == 0x64 && g_vm.visu.speed > 1)
		--g_vm.visu.speed;
	else if (key == 0x49 && g_vm.visu.speed < VISU_CPS_MAX - 9)
		g_vm.visu.speed += 10;
	else if (key == 0x44 && g_vm.visu.speed > 10)
		g_vm.visu.speed -= 10;
	else
		return ;
	visu_cps();
}

bool				visu_get_key(void)
{
	uint32_t		key;

	if ((key = getch()) != ERR)
	{
		mvprintw(VISU_ARENA_TB, VISU_VS + 3, ft_ultostr(key, 16, 0));
		if (key == 0x70)
			g_vm.visu.state = false;
		else if (key == 0x20)
			g_vm.visu.state = !g_vm.visu.state;
		else if (key == 0x71 || key == 0x51)
		{
			endwin();
			exit(EXIT_SUCCESS);
		}
		else
			visu_get_speed_key(key);
	}
	visu_state();
	return (g_vm.visu.state);
}
