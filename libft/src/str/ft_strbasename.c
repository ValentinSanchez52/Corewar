/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbasename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:19:49 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 21:19:59 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strbasename(char *name)
{
	char *nopath;
	char *noext;

	nopath = ft_strrchr(name, '/');
	if (nopath)
		nopath++;
	else
		nopath = name;
	if ((noext = ft_strrchr(nopath, '.')))
		return (ft_strndup(nopath, noext - nopath));
	else
		return (ft_strdup(nopath));
}
