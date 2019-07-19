/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap_manipulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:07:31 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/19 22:45:46 by njiall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/hashmap.h"
#include "include/libft.h"

/*
** Create an entry to use in the hashmap.
*/

t_hash_entry		*ft_hash_entry_create(
		const uint8_t *key,
		void *value
)
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

bool				ft_hashmap_get(
		t_hashmap *map,
		const uint8_t *key,
		void **value
)
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

void				*ft_hashmap_set(
		t_hashmap *map,
		const uint8_t *key,
		void *value
)
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

void				*ft_hashmap_remove(
		t_hashmap *map,
		const uint8_t *key
)
{
	uint16_t		hash;
	t_hash_entry	*e;
	t_hash_entry	*p;
	void			*old_value;

	hash = ft_hash_djb2(key);
	e = map->table[hash];
	p = NULL;
	while (e && strcmp((const char*)((void*)e->key), (const char*)(key)))
	{
		p = e;
		e = e->next;
	}
	if (!e)
		return (NULL);
	if (!p)
		map->table[hash] = e->next;
	else
		p->next = e->next;
	old_value = e->value;
	map->length--;
	free(e->key);
	free(e);
	return (old_value);
}

t_hash_entry		*ft_hashmap_iterate(
		t_hashmap *map,
		uint32_t *i,
		uint32_t *j
)
{
	uint32_t		k;
	t_hash_entry	*entry;

	while (*i < 0x10000)
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
