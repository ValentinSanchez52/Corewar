/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 14:15:06 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/04 16:08:47 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

static inline bool	edge_values(double d, char **s)
{
	if (d != d)
	{
		(*s)[0] = 'N';
		(*s)[1] = 'a';
		(*s)[2] = 'N';
		(*s)[3] = '\0';
		return (true);
	}
	else if (ft_isinf(d))
	{
		(*s)[0] = 'I';
		(*s)[1] = 'n';
		(*s)[2] = 'f';
		(*s)[3] = '\0';
		return (true);
	}
	return (false);
}

char				*ft_dtostr(double d, uint32_t precision, bool force_sign)
{
	static char		fmt[256];
	char			*s;

	s = fmt;
	if (d >= 0.0 && force_sign)
		*s++ = '+';
	else if (d < 0.0)
		*s++ = '-';
	if (edge_values(d, &s))
		return (fmt);
	ft_strcpy(s, ft_ultostr((uint64_t)d, 10, true));
	s += ft_strlen(s);
	if ((t_double){.d = d}.mantisa && precision > 0)
	{
		long fraction = (d - ((long)d)) * pow(10, precision);
		*s++ = '.';
		ft_strcpy(s, ft_ultostr(fraction, 10, true));
		precision -= ft_strlen(s) - 1;
		s += ft_strlen(s);
		while (precision-- > 1)
			*s++ = '0';
		s[0] = '\0';
	}
	return (fmt);
}
