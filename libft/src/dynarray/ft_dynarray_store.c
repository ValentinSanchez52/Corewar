/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynarray_store.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:55:07 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/31 05:05:56 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynarray.h"

#include <stdlib.h>
#include <string.h>

static inline t_dynarray*dynarray_fits_resize(t_dynarray *arr, uint64_t size)
{
	if (arr->size <= arr->index + size)
	{
		while (arr->size <= arr->index + size)
			arr->size <<= 1u;
		return (ft_dynarray_resize(arr, arr->size));
	}
	return (arr);
}

void					*dynarray_push_store(t_dynarray *arr, void *elem
										, uint64_t size)
{
	if (!(arr = dynarray_fits_resize(arr, size))->array && arr)
	{
		if (arr)
			free(arr);
		return (NULL);
	}
	memcpy(arr->array + arr->index, elem, size);
	arr->index += size;
	return (arr->array + arr->index - size);
}

void					*dynarray_set_store(t_dynarray *arr, uint64_t index
										, void *elem, uint64_t size)
{
	if (!(arr = dynarray_fits_resize(arr, size))->array && arr)
	{
		free(arr);
		return (NULL);
	}
	memcpy(arr->array + index, elem, size);
	return (arr->array);
}

void					*dynarray_insert_store(t_dynarray *arr, uint64_t index
										, void *elem, uint64_t size)
{
	if (!(arr = dynarray_fits_resize(arr, size))->array && arr)
	{
		free(arr);
		return (NULL);
	}
	memmove(arr->array + index + size, arr->array + index, arr->index - index);
	memcpy(arr->array + index, elem, size);
	arr->index += size;
	return (arr->array + index);
}
