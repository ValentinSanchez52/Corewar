/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mem_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 08:42:54 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 08:47:57 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				set_mem_value(uint32_t index, uint32_t value,
		uint32_t size)
{
	if (size > 4)
	{
		printf("WARNING: Use of set_mem_value with wrong size\n");
		size = 4;
	}
	while (size > 0)
	{
		vm.arena[index + size] = (uint8_t)value;
		value >>= 8;
		size--;
	}
}
