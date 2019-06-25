/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:05:49 by mbeilles          #+#    #+#             */
/*   Updated: 2019/06/25 14:34:09 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "hashmap.h"
#include "bboa.h"
#include "libft.h"
#include "dynarray.h"

static inline uint64_t	bboa_get_max_len_strs(t_dynarray *strs)
{
	t_usage_str		*us;
	uint64_t		i;
	uint64_t		max;

	max = 0;
	i = 0;
	while ((us = ft_dynarray_iterate(strs, &i, sizeof(t_usage_str))))
		if (us->len > max)
			max = us->len;
	return (max);
}

static inline void		bboa_push_option(
		t_dynarray *msg,
		t_usage_str *us,
		uint64_t i,
		uint64_t max_len
)
{
	uint64_t			j;

	if (i < 2)
		ft_dynarray_push(msg, (us->len > 1) ? "--" : " -", 2);
	else
		ft_dynarray_push(msg, (us->len > 1) ? "    --" : "     -", 6);
	ft_dynarray_push(msg, us->first, us->len);
	if (us->desc)
	{
		j = us->len;
		while (++j < max_len)
			ft_dynarray_push(msg, " ", 1);
		ft_dynarray_push(msg, us->desc, ft_strlen(us->desc));
		free(us->desc);
	}
}

static inline char		*bboa_get_formated_usage(
		t_dynarray *strs,
		uint64_t max_len
)
{
	char				*s;
	t_dynarray			*msg;
	t_usage_str			*us;
	uint64_t			i;

	if (!(msg = ft_dynarray_create(0, 0)))
		ft_exit(1, "No space left on device.\n", NULL);
	i = 0;
	while ((us = ft_dynarray_iterate(strs, &i, sizeof(t_usage_str))))
	{
		bboa_push_option(msg, us, i, max_len);
		if (i < strs->index / sizeof(t_usage_str))
			ft_dynarray_push(msg, "\n", 1);
	}
	ft_dynarray_push(msg, "", 1);
	ft_dynarray_destroy(strs, true);
	s = (char*)msg->array;
	free(msg);
	return (s);
}

static inline void		gen_option_with_types(
		t_dynarray *s,
		char *key,
		t_opt_match *entry
)
{
	static const char	*type_display[BBOA_AT_MAX_TYPE] = {
		[BBOA_AT_NONE] = "<_>",
		[BBOA_AT_STRING] = "<argument>",
		[BBOA_AT_NUMBER] = "<number>",
		[BBOA_AT_BOOLEAN] = "<bool>",
	};
	const char			*type;
	uint8_t				i;
	uint8_t				len;

	ft_dynarray_push(s, key, ft_strlen(key));
	len = entry->arg_count;
	ft_dynarray_push(s, " ", len > 0);
	i = -1;
	while (++i < len)
	{
		type = type_display[entry->types[i]];
		ft_dynarray_push(s, (void*)type, ft_strlen(type));
		ft_dynarray_push(s, " ", (i < len - 1));
	}
	ft_dynarray_push(s, "", 1);
}

char					*bboa_get_usage(t_hashmap *options)
{
	t_dynarray			*strs;
	t_hash_entry		*val;
	t_dynarray			*s;
	uint32_t			j;
	uint16_t			i;

	if (!(strs = ft_dynarray_create(4096, 4096)))
		ft_exit(1, "No space left on device.\n", NULL);
	i = 0;
	j = 0;
	while ((val = ft_hashmap_iterate(options, &i, &j)))
	{
		if (!(s = ft_dynarray_create(4096, 4096)))
			ft_exit(1, "No space left on device.\n", NULL);
		gen_option_with_types(s, (char*)val->key, val->value);
		ft_dynarray_push(strs, &(t_usage_str){
				.first = (char*)s->array, .len = ft_strlen((char*)s->array),
				.desc = ((((t_opt_match*)val->value)->desc) ? ft_strajoin(2,
							" - ", ((t_opt_match*)val->value)->desc) : NULL),
		}, sizeof(t_usage_str));
	}
	qsort(strs->array, strs->index / sizeof(t_usage_str), sizeof(t_usage_str),
			&bboa_compare_usage_str);
	return (bboa_get_formated_usage(strs, bboa_get_max_len_strs(strs) + 1));
}
