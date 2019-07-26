/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_load_arena.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:28:42 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 08:01:53 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "corewar.h"
#include "libft.h"
#include "dynarray.h"

static inline void	load_warriors_in_arena(void)
{
	t_process		process;
	static uint8_t	spawn_i;
	uint8_t			warrior_i;

	warrior_i = 0;
	while (warrior_i < 4 && spawn_i < 4)
	{
		if (vm.warriors[warrior_i].id)
		{
			ft_memcpy(&(vm.arena[spawn_i * COR_ARENA_SIZE / vm.warriors_nb]),
					vm.warriors[warrior_i].assembly,
					vm.warriors[warrior_i].assembly_size);
			process = (t_process){
					.registers[0] = vm.warriors[warrior_i].id,
					.global_offset = spawn_i * COR_ARENA_SIZE / vm.warriors_nb};
			ft_dynarray_insert(&vm.process, 0, &process,
					sizeof(t_process));
			spawn_i++;
		}
		warrior_i++;
	}
}

void				corewar_load_arena(void)
{
	vm.process = ft_dynarray_create_loc(0, 0);
	vm.instructions = ft_dynarray_create_loc(0, 0);
	load_warriors_in_arena();
	print_warriors();
	print_arena();
	/* print_processes(); */
}
