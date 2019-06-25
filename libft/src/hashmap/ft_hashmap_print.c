/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:56:41 by mbeilles          #+#    #+#             */
/*   Updated: 2019/06/14 15:12:52 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynarray.h"
#include "hashmap.h"

void			ft_hashmap_print(t_hashmap *map)
{
	t_hash_entry	*entry;
	t_dynarray		*string;
	char			*str;
	uint16_t		i;
	uint32_t		j;

	i = 0;
	j = 0;
	if (!(string = ft_dynarray_create(0, 0)))
		return ;
	while ((entry = ft_hashmap_iterate(map, &i, &j)))
	{
		str = ft_ultostr(ft_hash_djb2(entry->key, 16, true));
		ft_dynarray_push(string, str, ft_strlen(str));
		ft_dynarray_push(string, " : ", 3);
		str = entry->key;
		ft_dynarray_push(string, str, ft_strlen(str));
	}
}
