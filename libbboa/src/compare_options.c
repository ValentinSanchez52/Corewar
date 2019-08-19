/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:34:42 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 20:44:14 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bboa.h"
#include "libft.h"

inline bool				bboa_is_double(char *av)
{
	return (av && av[0] == '-' && av[1] == '-');
}

inline bool				bboa_is_single(char *av)
{
	return (av && av[0] == '-');
}

int						bboa_compare_usage_str(
		const void *str1,
		const void *str2
)
{
	int					comp;
	char				*s1;
	char				*s2;

	s1 = ((t_usage_str*)str1)->first;
	s2 = ((t_usage_str*)str2)->first;
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			break ;
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}
