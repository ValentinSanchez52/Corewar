/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdouble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 04:49:38 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/01 05:34:18 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline bool					ft_isdouble(const char *s)
{
	while (ft_isspace(*s))
		s++;
	if (!*s)
		return (false);
	if (*s == '-' || *s == '+')
		s++;
	while (*s && ft_isdigit(s[1]))
		s++;
	if ((ft_isdigit(*s) && s[1] == '.' && !ft_isspace(s[1]))
			|| (ft_isspace(*s) && s[1] == '.' && ft_isdigit(s[2])))
		s += 1 + ft_isdigit(*s);
	else if (*s && !ft_isdigit(*s) && !ft_isspace(*s))
		return (false);
	while (ft_isdigit(*s))
		s++;
	return (!*s || ft_isspace(*s));
}
