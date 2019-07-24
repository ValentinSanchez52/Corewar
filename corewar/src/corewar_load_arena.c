/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_load_arena.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:28:42 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/24 16:00:16 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "corewar.h"
#include "../../libft/include/libft.h"
#include "../../libft/include/dynarray.h"

static inline
void				load_warriors_in_arena(void)
{
	static uint8_t	spawn_i;
	uint8_t			warrior_i;

	warrior_i = 0;
	while (warrior_i < 4 && spawn_i < 4)
	{
		if (vm.warriors[warrior_i].id)
			ft_memcpy(&(vm.arena[spawn_i++ * COR_ARENA_SIZE / vm.warriors_nb]),
					vm.warriors[warrior_i].assembly,
					vm.warriors[warrior_i].assembly_size);
		warrior_i++;
	}
}

/*
** Prints a 64 * 64 map representing the Arena
*/

void				print_arena(void)
{
	uint8_t			line_i;
	uint8_t			column_i;

	line_i = -1;
	while (++line_i < 64)
		{
			column_i = -1;
			while (++column_i < 64)
				printf("%s%3.2x%s", vm.arena[line_i * 64 + column_i] > 0 ? YEL : "",
						vm.arena[line_i * 64 + column_i],
						vm.arena[line_i * 64 + column_i] > 0 ? NRM : "");
			printf("\n");
		}
}

void				corewar_load_arena(void)
{
	vm.process = ft_dynarray_create_loc(0, 0);
	vm.instructions = ft_dynarray_create_loc(0, 0);
	load_warriors_in_arena();
	print_warriors();
	print_arena();
}
