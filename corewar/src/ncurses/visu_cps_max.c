/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_cps_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 16:27:23 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/13 16:50:39 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <unistd.h>

inline void				cps_max(void)
{
	uint16_t		cycle;

	cycle = 0;
	while (cycle++ < 256)
	{
		visu_get_key();
		usleep(1000000 / (uint32_t)(g_vm.visu.speed * 256));
	}
}
