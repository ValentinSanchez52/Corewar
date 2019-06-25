/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:09:46 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/31 05:10:22 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

char			*ft_ltostr(int64_t i, uint8_t radix, uint8_t upcase)
{
	char		*s;
	int			flg;

	flg = 0;
	if (i < 0)
	{
		flg++;
		i = -i;
	}
	s = ft_ultostr(i, radix, upcase);
	if (s && flg)
		*--s = '-';
	return (s);
}
