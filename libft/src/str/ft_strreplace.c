/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 10:42:03 by mbeilles          #+#    #+#             */
/*   Updated: 2019/06/14 13:27:28 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dynarray.h"

char			*ft_strreplace(
		const char *src,
		const char *pattern,
		const char *replace
)
{
	t_dynarray	*str;
	char		*str_buffer;
	int			plen;
	int			rlen;
	uint64_t	i;

	i = ft_strlen(src);
	if (!(str = ft_dynarray_create(i + ft_strlen(replace), 0)))
		return (NULL);
	ft_dynarray_push(str, (void*)src, i);
	ft_dynarray_push(str, "", 1);
	i = 0;
	plen = ft_strlen(pattern);
	rlen = ft_strlen(replace);
	while (ft_dynarray_iterate(str, &i, 1))
		if (ft_strnequ((char*)str->array + i - 1, pattern, plen))
		{
			ft_dynarray_remove(str, i - 1, plen);
			ft_dynarray_insert(str, i - 1, (void*)replace, rlen);
			i += rlen - 1;
		}
	str_buffer = (char*)str->array;
	free(str);
	return (str_buffer);
}
