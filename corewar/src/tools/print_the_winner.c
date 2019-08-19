/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_the_winner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:57:33 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/19 13:10:45 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	return (-1);
}

void				print_the_winner(void)
{
	uint8_t			warrior_id;
	int8_t			winner;

	winner = get_first_warrior();
	warrior_id = -1;
	while (++warrior_id < COR_WARRIOR_NB_MAX)
		if (g_vm.warriors[warrior_id].id)
		{
			if (g_vm.warriors[warrior_id].cycle_last
					> g_vm.warriors[winner].cycle_last)
				winner = warrior_id;
		}
	if (winner >= 0)
	{
		write(1, "Winner is: ", 11);
		write(1, g_vm.warriors[winner].name,
				ft_strlen(g_vm.warriors[winner].name));
		write(1, "\n", 1);
	}
	else
		write(1, "No winner :(\n", 13);
}
