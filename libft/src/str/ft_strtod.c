/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 09:44:35 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/31 04:58:54 by mbeilles         ###   ########.fr       */
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
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' && str++)
		fact = -1.0F;
	point_seen = false;
	while (*str)
	{
		if (!point_seen && *str == '.')
			point_seen = true;
		else if (*str >= '0' && *str <= '9')
		{
			if (point_seen)
				fact /= 10.0F;
			rez = rez * 10.0F + (double)(*str - '0');
		}
		str++;
	}
	return (rez * fact);
}
