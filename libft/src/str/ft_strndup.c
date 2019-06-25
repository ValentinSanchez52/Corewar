/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 11:27:37 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/03 05:20:50 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strndup(const char *str, size_t n)
{
	char		*s;

	if (!(s = (char *)malloc(n + 1)))
		return (NULL);
	s[n] = '\0';
	return (ft_strncpy(s, str, n));
}
