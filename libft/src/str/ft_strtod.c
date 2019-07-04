/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:44:35 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/04 16:35:17 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include "libft.h"

double						ft_strtod(const char *str, char **endptr)
{
	double					rez;
	double					fact;
	bool					point_seen;

	rez = 0;
	fact = 1;
	*endptr = (char*)str;
	while (**endptr && ft_isspace(*str))
		(*endptr)++;
	if (**endptr == '-' && (*endptr)++)
		fact = -1.0F;
	point_seen = false;
	while (**endptr)
	{
		if (!point_seen && **endptr == '.')
			point_seen = true;
		else if (**endptr >= '0' && **endptr <= '9')
		{
			if (point_seen)
				fact /= 10.0F;
			rez = rez * 10.0F + (double)(**endptr - '0');
		}
		(*endptr)++;
	}
	return (rez * fact);
}
