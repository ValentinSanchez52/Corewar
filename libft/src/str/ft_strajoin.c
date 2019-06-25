/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strajoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:55:58 by mbeilles          #+#    #+#             */
/*   Updated: 2019/04/25 19:33:10 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>

static inline int	ft_stralen(int len, va_list list)
{
	int				slen;
	char			*str;

	slen = 0;
	while (len-- > 0)
		slen += ft_strlen(va_arg(list, char *));
	return (slen);
}

inline char			*ft_strajoin(int len, ...)
{
	va_list			arg;
	va_list			cpy;
	char			*str;
	char			*buffer;

	va_start(arg, len);
	va_copy(cpy, arg);
	if (!(buffer = malloc(ft_stralen(len, cpy) + 1)))
		return (NULL);
	buffer[0] = '\0';
	while (len-- > 0)
	{
		str = va_arg(arg, char *);
		ft_strcat(buffer, str);
	}
	va_end(arg);
	return (buffer);
}
