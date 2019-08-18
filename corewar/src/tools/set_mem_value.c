/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mem_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 08:42:54 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/18 12:43:20 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				set_mem_value(uint32_t index, uint32_t value,
		uint32_t size, t_arena_own claim_id)
{
	/*printf("index: %d, value: %d, size: %d\n", index, value, size);*/
	if (size > 4)
	{
		printf("WARNING: Use of set_mem_value with wrong size\n");
		size = 4;
	}
	while (size > 0)
	{
		g_vm.arena[(((uint16_t)index % 4096) + size - 1) % 4096]
			= (uint8_t)value;
		g_vm.arena_claim[(((uint16_t)index % 4096) + size - 1) % 4096]
			= claim_id;
		value >>= 8;
		size--;
	}
}
