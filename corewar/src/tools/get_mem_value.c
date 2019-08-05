/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mem_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:10 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/05 18:37:40 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	/* printf("Value reading: %u:%u -> ", index, size); */
	while (size > 0)
	{
		value = value << 8;
		/* printf("%02hhx ", get_mem_cell(index)); */
		value += get_mem_cell(index);
		index++;
		size--;
	}
	/* printf("\n"); */
	return (value);
}
