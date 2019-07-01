/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynarray_manipulate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:04:46 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/01 15:20:23 by njiall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dynarray.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static inline t_dynarray*ft_dynarray_fits_resize(t_dynarray *arr, uint64_t size)
{
	if (arr->size <= arr->index + size)
	{
		while (arr->size <= arr->index + size)
			arr->size <<= 1u;
		arr->array = realloc(arr->array, arr->size);
	}
	return (arr);
}

void					*ft_dynarray_push(t_dynarray *arr, void *elem
										, uint64_t size)
{
	if (!(arr = ft_dynarray_fits_resize(arr, size))->array)
	{
		if (arr)
			free(arr);
		ft_exit(1, "No space left on device.\n", NULL);
	}
	memcpy(arr->array + arr->index, elem, size);
	arr->index += size;
	return ((void*)arr->index - size);
}

void					*ft_dynarray_set(t_dynarray *arr, uint64_t index,
										void *elem, uint64_t size)
{
	if (!(arr = ft_dynarray_fits_resize(arr, size))->array)
	{
		if (arr)
			free(arr);
		ft_exit(1, "No space left on device.\n", NULL);
	}
	memcpy(arr->array + index, elem, size);
	return ((void*)index);
}

void					*ft_dynarray_get(t_dynarray *arr, uint64_t index,
										uint64_t size)
{
	if (index * size < arr->index)
		return (arr->array + index * size);
	return (NULL);
}

void					*ft_dynarray_insert(t_dynarray *arr, uint64_t index
										, void *elem, uint64_t size)
{
	if (!(arr = ft_dynarray_fits_resize(arr, size))->array)
	{
		if (arr)
			free(arr);
		ft_exit(1, "No space left on device.\n", NULL);
	}
	memmove(arr->array + index + size, arr->array + index, arr->index - index);
	memcpy(arr->array + index, elem, size);
	arr->index += size;
	return ((void*)index);
}
