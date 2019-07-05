/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynarray_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:05:03 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/05 15:06:55 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dynarray.h"

void				*ft_dynarray_remove(t_dynarray *arr, uint64_t index
										, uint64_t size)
{
	memmove(arr->array + index, arr->array + index + size,
			arr->index - index - size);
	arr->index -= size;
	if (arr->index + size < arr->size / 4
			&& arr->min_size > arr->size / 4
			&& !ft_dynarray_resize(arr, arr->size / 2))
		return (NULL);
	return (arr->array + arr->index);
}

void				*ft_dynarray_remove_address(t_dynarray *arr
									, void *address, uint64_t size)
{
	if (!(address >= (void*)arr->array)
			|| !(address + size < (void*)arr->array + arr->index))
		memmove(address, address + size
			, arr->index - (address - (void*)arr->array) - size);
	arr->index -= size;
	if (arr->index + size < arr->size / 4
			&& arr->min_size > arr->size / 4
			&& !ft_dynarray_resize(arr, arr->size / 2))
		return (NULL);
	return (arr->array + arr->index);
}

void				*ft_dynarray_purge(t_dynarray *arr)
{
	arr->index = 0;
	if (arr->size > arr->min_size && !ft_dynarray_resize(arr, arr->min_size))
		return (NULL);
	return (arr->array);
}

void				ft_dynarray_destroy(t_dynarray *arr, bool is_alloc)
{
	free(arr->array);
	if (is_alloc)
		free(arr);
}
