/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mem_cell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:10 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/10 19:18:40 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

inline uint8_t			get_mem_cell(uint32_t index)
{
	return (g_vm.arena[index & (COR_ARENA_SIZE - 1)]);
}
