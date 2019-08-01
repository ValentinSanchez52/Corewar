/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islong.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 05:15:37 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/01 05:34:24 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline bool			ft_islong(const char *s)
{
	while (ft_isspace(*s))
		s++;
	if (!*s)
		return (false);
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
		s++;
	while (ft_isspace(*s))
		s++;
	return (!*s);
}
