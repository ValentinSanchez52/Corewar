/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynarray_iterate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:02:02 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/31 05:02:23 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynarray.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void				*ft_dynarray_iterate(t_dynarray *arr, uint64_t *iterator,
											uint64_t size)
{
	if (*iterator * size < arr->index)
	{
		(*iterator)++;
		return (arr->array + (*iterator - 1) * size);
	}
	return (NULL);
}
