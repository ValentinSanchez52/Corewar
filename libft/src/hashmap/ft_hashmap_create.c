/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:06:48 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/31 05:06:49 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"

/*
** This creates and initialize the hashmap.
** 		There is a trick there to test out. This is actually commented
** 		for testing reasons.
*/

t_hashmap			*ft_hashmap_create(void)
{
	t_hashmap		*map;

	if (!(map = (t_hashmap*)malloc(sizeof(t_hashmap))))
		return (NULL);
	if (!(map->table = (t_hash_entry**)malloc(sizeof(t_hash_entry*)
														* HASHTABLE_SIZE)))
		return (NULL);
	map->length = 0;
	memset(map->table, 0, sizeof(*map->table) * HASHTABLE_SIZE);
	return (map);
}

uint32_t			ft_hashmap_destroy(t_hashmap *map)
{
	t_hash_entry	*tmp;
	t_hash_entry	*e;
	uint32_t		i;
	uint32_t		r;

	i = ~0u;
	r = 0;
	while (++i < (2 << 16))
	{
		e = map->table[i];
		while (e)
		{
			tmp = e->next;
			free(e->key);
			free(e);
			e = tmp;
			++r;
		}
	}
	free(map->table);
	free(map);
	++r;
	return (r);
}
