/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynarray_push_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:44:06 by mbeilles          #+#    #+#             */
/*   Updated: 2019/05/25 10:48:57 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dynarray.h"

static inline t_dynarray*ft_dynarray_fits_resize(t_dynarray *arr, uint64_t size)
{
	if (arr->size <= arr->index + size)
	{
		while (arr->size <= arr->index + size)
			arr->size <<= 1u;
		return (ft_dynarray_resize(arr, arr->size));
	}
	return (arr);
}

void					*ft_dynarray_push_str(t_dynarray *arr, void *elem)
{
	uint32_t			size;

	size = ft_strlen(elem);
	if (!(arr = ft_dynarray_fits_resize(arr, size))->array)
	{
		if (arr)
			free(arr);
		return (NULL);
	}
	memcpy(arr->array + arr->index, elem, size);
	arr->index += size;
	return (arr->array + arr->index - size);
}
