/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_the_winner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:57:33 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/19 19:09:53 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static const char * const	g_claim_col[COR_ARN_MAX] = {
	[COR_ARN_NO_CLAIM] = "\e[37m",
	[COR_ARN_W1_CLAIM] = "\e[1;33m",
	[COR_ARN_W2_CLAIM] = "\e[1;34m",
	[COR_ARN_W3_CLAIM] = "\e[1;31m",
	[COR_ARN_W4_CLAIM] = "\e[1;35m",
};

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
		print_vm((t_print){.printer = printer, .level = LOG_INFO,
				.data = ft_strajoin(4, "The winner is: ",
						g_claim_col[winner + 1], g_vm.warriors[winner].name,
						"\e[0m\n"), .destructor = &free});
	else
		print_vm((t_print){.printer = printer, .level = LOG_INFO,
				.data = "No Winner :("});
}
