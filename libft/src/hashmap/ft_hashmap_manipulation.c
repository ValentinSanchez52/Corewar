/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap_manipulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:07:31 by mbeilles          #+#    #+#             */
/*   Updated: 2019/06/14 14:01:39 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hashmap.h"
#include "libft.h"

/*
** Create an entry to use in the hashmap.
*/

t_hash_entry		*ft_hash_entry_create(const uint8_t *key, void *value)
{
	t_hash_entry	*e;

	if (!(e = (t_hash_entry*)malloc(sizeof(t_hash_entry))))
		return (NULL);
	*e = (t_hash_entry){(uint8_t*)ft_strdup((const char*)((void*)key))
		, value, NULL};
	return (e);
}

/*
** Returns the value of an entry in the hashmap for a given key.
** If the key doesn't match a Null pointer is returned.
*/

bool				ft_hashmap_get(t_hashmap *map
					, const uint8_t *key, void **value)
{
	uint16_t		hash;
	t_hash_entry	*entry;

	hash = ft_hash_djb2(key);
	entry = map->table[hash];
	while (entry && strcmp((char*)((void*)entry->key), (char*)((void*)key)))
		entry = entry->next;
	if (entry)
	{
		if (value)
			*value = entry->value;
		return (true);
	}
	return (false);
}

/*
** Sets the value of an entry given a key.
** If the entry doesn't exist it's created and then set.
** If the entry already exists then it replaces the previous value
** 	by the new one and returns the old one.
** This will need to be refactored.
*/

void				*ft_hashmap_set(t_hashmap *map
					, const uint8_t *key, void *value)
{
	uint16_t		hash;
	t_hash_entry	*head;
	t_hash_entry	*prev;
	void			*old_value;

	hash = ft_hash_djb2(key);
	head = map->table[hash];
	prev = NULL;
	while (head && strcmp((const char*)((void*)head->key), (const char*)(key)))
	{
		prev = head;
		head = head->next;
	}
	old_value = NULL;
	if (head == NULL && ++map->length)
		if (prev == NULL)
			map->table[hash] = ft_hash_entry_create(key, value);
		else
			prev->next = ft_hash_entry_create(key, value);
	else
	{
		old_value = head->value;
		head->value = value;
	}
	return (old_value);
}

/*
** Removes an entry from the hashmap and the returns the value that was stored.
*/

void				*ft_hashmap_remove(t_hashmap *map, const uint8_t *key)
{
	t_hash_entry	**indirect;
	t_hash_entry	*e;
	void			*data;

	e = map->table[ft_hash_djb2(key)];
	indirect = &e;
	while ((*indirect) && !strcmp((const char*)((void*)(*indirect)->key)
				, (const void*)((void*)key)))
		indirect = &(*indirect)->next;
	*indirect = e->next;
	data = (void*)e->value;
	free(e->key);
	free(e);
	return (data);
}

t_hash_entry		*ft_hashmap_iterate(t_hashmap *map, uint16_t *i,
										uint32_t *j)
{
	uint32_t		k;
	t_hash_entry	*entry;

	while (*i < 0xffff)
	{
		if (map->table[*i])
		{
			k = 0;
			entry = map->table[*i];
			while (entry && k < *j && ++k)
				entry = entry->next;
			*j += 1;
			if (entry)
				return (entry);
		}
		*i += 1;
		*j = 0;
	}
	return (NULL);
}
