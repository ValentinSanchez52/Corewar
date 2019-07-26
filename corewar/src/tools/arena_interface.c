/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_interface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:10 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 06:02:13 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

inline void			set_mem_value(uint32_t index, uint32_t value, uint32_t size)
{
	if (size > 4)
	{
		printf("WARNING: Use of set_mem_value with wrong size\n");
		size = 4;
	}
	while (size > 0)
	{
		printf("CC\n");
		vm.arena[(index + size) & 4095] = (uint16_t)value;
		value = value >> 8;
		size--;
	}
}

inline uint8_t		get_mem_cell(uint32_t index)
{
	return (vm.arena[index & 4095]);
}

/*
**	returns an uint32_t which contains 
*/

inline uint32_t		get_mem_value(uint32_t index, uint32_t size)
{
	uint32_t		value;

	value = 0;
	if (size > 4)
	{
		printf("WARNING: Use of get_mem_value with wrong size\n");
		size = 4;
	}
	while (size > 0)
	{
		value = value << 8;
		value += get_mem_cell(index);
		index++;
		size--;
	}
	return (value);
}
