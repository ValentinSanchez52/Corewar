/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:29:54 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/08 17:15:02 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "corewar.h"
#include "libft.h"
#include "dynarray.h"

/*
**	Prints a 64 * 64 map representing the Arena
*/

void				print_arena(void)
{
	uint8_t			line_i;
	uint8_t			column_i;

	printf(YEL"Arena:"NRM"\n");
	line_i = -1;
	while (++line_i < 64)
	{
		column_i = -1;
		while (++column_i < 64)
			printf("%s%3.2x%s", vm.arena[line_i * 64 + column_i] > 0
					? YEL : "", vm.arena[line_i * 64 + column_i],
					vm.arena[line_i * 64 + column_i] > 0 ? NRM : "");
		printf("\n");
	}
}

void				print_warriors(void)
{
	uint8_t			warrior_i;

	warrior_i = 0;
	write(1, "===================[ Warriors ]===================\n", 51);
	while (warrior_i < 4)
	{
		if (vm.warriors[warrior_i].id)
			print_warrior(vm.warriors + warrior_i, warrior_i, true);
		warrior_i++;
	}
	write(1, "=====================[ End ]======================\n", 51);
}
