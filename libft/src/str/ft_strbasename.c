/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbasename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njiall <mbeilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 04:38:00 by njiall            #+#    #+#             */
/*   Updated: 2019/07/06 04:46:15 by njiall           ###   ########.fr       */
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
