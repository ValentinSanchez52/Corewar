/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 22:33:43 by mbeilles          #+#    #+#             */
/*   Updated: 2019/01/11 04:02:33 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

char			*ft_ultostr(uint64_t u, uint8_t radix, uint8_t upcase)
{
	static char	buff[34];
	uint64_t	c;
	char		*s;

	s = buff + sizeof(buff);
	*--s = '\0';
	if (u)
		while (u)
		{
			c = u % radix;
			u /= radix;
			if (c > 9)
				*--s = ((upcase) ? 'A' : 'a') - 10 + c;
			else
				*--s = '0' + c;
		}
	else
		*--s = '0';
	return (s);
}
