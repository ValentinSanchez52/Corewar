/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_load_arena.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:28:42 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/09 21:04:22 by njiall           ###   ########.fr       */
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
		if (g_vm.warriors[warrior_i].id)
		{
			ft_memcpy(&(g_vm.arena[spawn_i * COR_ARENA_SIZE / g_vm.warriors_nb]),
					g_vm.warriors[warrior_i].assembly,
					g_vm.warriors[warrior_i].assembly_size);
			printf("%u\n", warrior_i);
			ft_memset(&g_vm.arena_claim[spawn_i * COR_ARENA_SIZE / g_vm.warriors_nb], warrior_i + 1, g_vm.warriors[warrior_i].assembly_size);
			process = (t_process){
					.registers[0] = g_vm.warriors[warrior_i].id,
					.global_offset = spawn_i * COR_ARENA_SIZE / g_vm.warriors_nb};
			str_uuid_generate(process.uuid);
			ft_dynarray_push(&g_vm.process, &process, sizeof(t_process));
			spawn_i++;
		}
		warrior_i++;
	}
}

void				corewar_load_arena(void)
{
	g_vm.process = ft_dynarray_create_loc(0, 0);
	g_vm.process_queue = ft_dynarray_create_loc(0, 0);
	load_warriors_in_arena();
	print_warriors();
	/* print_arena(); */
	/* print_processes(); */
}
