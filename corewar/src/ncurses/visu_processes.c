/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 15:52:36 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 18:45:55 by vsanchez         ###   ########.fr       */
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

inline void				visu_processes(void)
{
	t_process		*process;
	uint64_t		process_id;
	uint8_t			color_id;
	uint16_t		index;

	process_id = 0;
	while ((process = ft_dynarray_iterate(&g_vm.process, &process_id,
					sizeof(t_process))))
	{
		index = process->global_offset % 4096 + process->pc % 4096;
		if (!(color_id = get_cell_claim(index)))
			color_id = 6;
		attron(COLOR_PAIR(color_id));
		attron(A_REVERSE);
		mvprintw(VISU_ARENA_TB + (index % 4096) / VISU_ARENA_WDTH,
				VISU_ARENA_LB + ((index % VISU_ARENA_WDTH) * 3),
				cell_format(ft_ultostr(get_mem_cell(index), 16, 0)));
		attroff(COLOR_PAIR(color_id));
		attroff(A_REVERSE);
	}
}
