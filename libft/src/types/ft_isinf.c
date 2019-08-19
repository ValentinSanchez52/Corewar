/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 14:39:19 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 21:20:54 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

int				ft_isinf(double x)
{
	t_sdouble	dd;
	int32_t		hx;
	int32_t		lx;

	dd = (t_sdouble){.d = x};
	hx = dd.e.msw;
	lx = dd.e.lsw;
	lx |= (hx & 0x7fffffff) ^ 0x7ff00000;
	lx |= -lx;
	return (~(lx >> 31) & (hx >> 30));
}
