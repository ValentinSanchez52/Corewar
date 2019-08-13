/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cell_claim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:15:31 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/10 19:19:02 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_arena_own				get_cell_claim(uint32_t index)
{
	return (g_vm.arena_claim[index & (COR_ARENA_SIZE - 1)]);
}
