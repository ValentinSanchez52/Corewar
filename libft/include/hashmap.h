/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 20:09:57 by mbeilles          #+#    #+#             */
/*   Updated: 2019/06/14 14:57:44 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdint.h>
# include <stdbool.h>

# define HASHTABLE_SIZE	(1u << 16)

typedef struct		s_hash_entry
{
	uint8_t				*key;
	void				*value;
	struct s_hash_entry	*next;
}					t_hash_entry;

typedef struct		s_hashmap
{
	t_hash_entry	**table;
	uint64_t		length;
}					t_hashmap;

t_hashmap			*ft_hashmap_create();
t_hash_entry		*ft_hash_entry_create(const uint8_t *key, void *value);
uint16_t			ft_hash_djb2(const uint8_t *str);

bool				ft_hashmap_get(
		t_hashmap *map,
		const uint8_t *key,
		void **value
);
void				*ft_hashmap_set(
		t_hashmap *map,
		const uint8_t *key,
		void *value
);
void				*ft_hashmap_remove(t_hashmap *map, const uint8_t *key);
t_hash_entry		*ft_hashmap_iterate(t_hashmap *map, uint16_t *interator,
										uint32_t *bucket_iterator);
void				ft_hash_print(t_hashmap *map);

#endif
