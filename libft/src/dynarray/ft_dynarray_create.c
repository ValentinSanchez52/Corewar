/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynarray_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:05:01 by mbeilles          #+#    #+#             */
/*   Updated: 2019/06/14 16:04:30 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynarray.h"

#include <stdlib.h>
#include <string.h>

/*
** Creates a dynarray with the size passed in the parameter.
**
** - integer 64 bits | size of the default array allocated.
*/

t_dynarray				*ft_dynarray_create(uint64_t min, uint64_t max)
{
	t_dynarray			*arr;

	if (min == 0)
		min = DYNARRAY_DEFAULT_SIZE;
	if (max == 0)
		max = DYNARRAY_DEFAULT_MAX;
	if (!(arr = malloc(sizeof(t_dynarray)))
		|| !(arr->array = malloc(min)))
	{
		if (arr)
			free(arr);
		return (NULL);
	}
	arr->index = 0u;
	arr->size = min;
	arr->min_size = min;
	arr->max_size = max;
	return (arr);
}

t_dynarray				*ft_dynarray_duplicate(t_dynarray *dyn)
{
	t_dynarray			*new;

	if (!(new = ft_dynarray_create(dyn->min_size, dyn->max_size)))
		return (NULL);
	ft_dynarray_push(new, dyn->array, dyn->index);
	return (new);
}
