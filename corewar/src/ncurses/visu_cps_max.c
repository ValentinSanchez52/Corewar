/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_cps_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:27:23 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/14 19:36:13 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <unistd.h>

inline void				cps_max(void)
{
	uint16_t		cycle;

	cycle = 0;
	if (g_vm.visu.speed > 150)
		return ;
	while (cycle++ < 256)
	{
		visu_get_key();
		usleep((800000 / (g_vm.visu.speed > 60 ? 3 : 1))
				/ (uint32_t)(g_vm.visu.speed * 256));
	}
}
