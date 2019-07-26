/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 17:29:54 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 08:03:23 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "corewar.h"
#include "libft.h"
#include "dynarray.h"

/*
**	Prints all processes
*/

void				print_processes(void)
{
	t_process		*process;
	uint64_t		process_i;

	printf(YEL"Processes:"NRM"\n");
	process_i = 0;
	while ((process = ft_dynarray_iterate(&(vm.process), &process_i,
					sizeof(t_process))))
	{
		printf("process: r1: %x\n", process->registers[0]);
	}
}

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

	printf(YEL"print_warriors"NRM"\n");
	warrior_i = 0;
	while (warrior_i < 4)
	{
		if (vm.warriors[warrior_i].id)
		{
			printf("warrior %s, id %i, comment %s, assembly %u, magic %x.\n",
					vm.warriors[warrior_i].name,
					vm.warriors[warrior_i].id,
					vm.warriors[warrior_i].comment,
					vm.warriors[warrior_i].assembly_size,
					vm.warriors[warrior_i].magic);
		}
		warrior_i++;
	}
}
