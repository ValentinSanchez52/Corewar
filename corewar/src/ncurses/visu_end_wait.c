/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_end_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:01:07 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/18 13:16:26 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

/*
**	endwin();	//To restore terminal settings
*/

static inline int8_t	get_first_warrior(void)
{
	uint8_t				warrior_id;

	warrior_id = 0;
	while (warrior_id < COR_WARRIOR_NB_MAX)
	{
		if (g_vm.warriors[warrior_id].id)
			return (warrior_id);
		warrior_id++;
	}
}

static inline int8_t	win_center(int8_t warrior_id)
{
	int8_t				winner_start;
	int8_t				sentence_len;

	winner_start = (VISU_ARENA_RB) / 2;
	sentence_len = 10 + ft_strlen(g_vm.warriors[warrior_id].name);
	winner_start -= sentence_len / 2;
	mvprintw((VISU_ARENA_BB) / 2 - 1, winner_start, "Winner is");
	return (winner_start + 10);
}

static inline void		print_winner(void)
{
	uint8_t			warrior_id;
	int8_t			winner;
	int8_t			win_centred;

	winner = get_first_warrior();
	warrior_id = -1;
	while (++warrior_id < COR_WARRIOR_NB_MAX)
		if (g_vm.warriors[warrior_id].id)
		{
			if (g_vm.warriors[warrior_id].cycle_last
					> g_vm.warriors[winner].cycle_last)
				winner = warrior_id;
		}
	win_centred = win_center(winner);
	if (winner >= 0)
	{
		attron(COLOR_PAIR(winner + 1));
		mvprintw((VISU_ARENA_BB) / 2 - 1, win_centred,
				g_vm.warriors[winner].name);
		attroff(COLOR_PAIR(winner + 1));
	}
	else
		mvprintw((VISU_ARENA_BB) / 2 - 1, (VISU_ARENA_RB - 61) / 2 + 1,
				"                       No winner :(                         ");
}

static inline void		set_winner_borders(void)
{
	attron(COLOR_PAIR(5));
	mvprintw((VISU_ARENA_BB) / 2 - 3, (VISU_ARENA_RB - 61) / 2,
			"**************************************************************");
	mvprintw((VISU_ARENA_BB) / 2 + 1, (VISU_ARENA_RB - 61) / 2,
			"**************************************************************");
	mvprintw((VISU_ARENA_BB) / 2 - 2, (VISU_ARENA_RB - 61) / 2, "*");
	mvprintw((VISU_ARENA_BB) / 2 - 2, (VISU_ARENA_RB + 61) / 2, "*");
	mvprintw((VISU_ARENA_BB) / 2 - 1, (VISU_ARENA_RB - 61) / 2, "*");
	mvprintw((VISU_ARENA_BB) / 2 - 1, (VISU_ARENA_RB + 61) / 2, "*");
	mvprintw((VISU_ARENA_BB) / 2, (VISU_ARENA_RB - 61) / 2, "*");
	mvprintw((VISU_ARENA_BB) / 2, (VISU_ARENA_RB + 61) / 2, "*");
	attroff(COLOR_PAIR(5));
}

inline void				visu_end_wait(void)
{
	uint32_t		key;

	set_winner_borders();
	mvprintw((VISU_ARENA_BB) / 2 - 2, (VISU_ARENA_RB - 61) / 2 + 1,
			"                                                            ");
	mvprintw((VISU_ARENA_BB) / 2 - 1, (VISU_ARENA_RB - 61) / 2 + 1,
			"                                                            ");
	mvprintw((VISU_ARENA_BB) / 2, (VISU_ARENA_RB - 61) / 2 + 1,
			"                                                            ");
	print_winner();
	while ((key = getch()) == ERR)
		continue ;
	endwin();
}
