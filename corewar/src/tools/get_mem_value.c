/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mem_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:13:10 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/26 06:13:37 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

inline uint32_t		get_mem_value(uint32_t index, uint32_t size)
{
	uint32_t		value;

	value = 0;
	while (size > 0)
	{
		value = value << 8;
		value += get_mem_cell(index);
		index++;
		size--;
	}
	return (value);
}
