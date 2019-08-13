/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:52:36 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 16:36:54 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

inline void				visu_processes(void)
{
	/*uint8_t			process_id;*/
	/*uint8_t			color_id;*/
	/*uint16_t		index;*/

	/*process_id = 0;*/
	/*while (process_id < NB_PROCESS)*/
	/*{*/
		/*index = g_vm.process[process_id].global_offset % 4096*/
			/*+ g_vm.process[process_id].pc % 4096;*/
		/*if (!(color_id = get_cell_claim(index)))*/
			/*color_id = 6;*/
		/*attron(COLOR_PAIR(color_id));*/
		/*attron(A_REVERSE);*/
		/*mvprintw(VISU_ARENA_TB + (index % 4096) / VISU_ARENA_WDTH,*/
				/*VISU_ARENA_LB + ((index % VISU_ARENA_WDTH) * 3),*/
				/*ft_ultostr(get_mem_cell(index), 16, 0));*/
		/*attroff(COLOR_PAIR(color_id));*/
		/*attroff(A_REVERSE);*/
		/*g_vm.process[process_id].pc++;*/
		/*process_id++;*/
	/*}*/
}
