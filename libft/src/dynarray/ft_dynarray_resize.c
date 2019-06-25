/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynarray_resize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:07:40 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/01 05:25:14 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynarray.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** Resizes the array of dynarray to the size.
**
** - dynarray    | dynarray to resize.
** - int 64 bits | size to apply.
*/

t_dynarray				*ft_dynarray_resize(t_dynarray *arr, uint64_t size)
{
	arr->size = size;
	arr->array = realloc(arr->array, size);
	return (arr);
}
