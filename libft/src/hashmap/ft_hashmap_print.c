/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:56:41 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/15 02:07:02 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "dynarray.h"
#include "hashmap.h"
#include "libft.h"

static inline uint64_t	get_entry_number(
		t_hashmap *map
)
{
	uint64_t		num;
	t_hash_entry	*e;
	uint32_t		i;
	uint32_t		j;

	i = 0;
	j = 0;
	num = 0;
	while ((e = ft_hashmap_iterate(map, &i, &j)))
		++num;
	return (num);
}

static inline void		append_entry(
		t_hash_entry *entry,
		t_dynarray *string
)
{
	char			*str;
	int				z;

	ft_dynarray_push(string, "Hash:  0x", 10);
	str = ft_ultostr(ft_hash_djb2(entry->key), 16, false);
	z = ft_strlen(str);
	while (++z <= 4)
		ft_dynarray_push(string, "0", 1);
	ft_dynarray_push(string, str, ft_strlen(str));
	ft_dynarray_push(string, " - Key: '", 9);
	str = (char*)entry->key;
	ft_dynarray_push(string, str, ft_strlen(str));
	ft_dynarray_push(string, "' Value: 0x", 11);
	str = ft_ultostr((uint64_t)entry->value, 16, false);
	ft_dynarray_push(string, str, ft_strlen(str));
	ft_dynarray_push(string, "\n", 1);
}

void					ft_hashmap_print(
		t_hashmap *map
)
{
	t_hash_entry	*entry;
	t_dynarray		*string;
	char			*str;
	uint32_t		i;
	uint32_t		j;

	i = 0;
	j = 0;
	if (!(string = ft_dynarray_create(0, 0)))
		return ;
	ft_dynarray_push(string, "Hashmap[", 8);
	str = ft_ultostr(get_entry_number(map), 10, false);
	ft_dynarray_push(string, str, ft_strlen(str));
	ft_dynarray_push(string, "]\n", 2);
	while ((entry = ft_hashmap_iterate(map, &i, &j)))
		append_entry(entry, string);
	write(1, string->array, string->index);
	ft_dynarray_destroy(string, true);
}
