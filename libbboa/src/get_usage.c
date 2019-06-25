/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:05:49 by mbeilles          #+#    #+#             */
/*   Updated: 2019/05/25 14:20:31 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "hashmap.h"
#include "bboa.h"
#include "libft.h"
#include "dynarray.h"

static int				bboa_compare_usage_str(
		const void *str1,
		const void *str2
)
{
	int					comp;
	char				*s1;
	char				*s2;

	s1 = ((t_usage_str*)str1)->first;
	s2 = ((t_usage_str*)str2)->first;
	while (*s1 && *s2)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			break ;
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}

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

char					*bboa_get_usage(t_hashmap *options)
{
	t_dynarray			*strs;
	t_hash_entry		*val;
	char				*s;
	uint32_t			j;
	uint16_t			i;

	if (!(strs = ft_dynarray_create(4096, 4096)))
		ft_exit(1, "No space left on device.\n", NULL);
	i = 0;
	j = 0;
	while ((val = ft_hashmap_iterate(options, &i, &j)))
	{
		s = (char*)val->key;
		ft_dynarray_push(strs, &(t_usage_str){
				.first = s, .len = ft_strlen(s),
				.desc = ((((t_opt_match*)val->value)->desc) ? ft_strajoin(2,
							" - ", ((t_opt_match*)val->value)->desc) : NULL),
		}, sizeof(t_usage_str));
	}
	qsort(strs->array, strs->index / sizeof(t_usage_str), sizeof(t_usage_str),
			&bboa_compare_usage_str);
	return (bboa_get_formated_usage(strs, bboa_get_max_len_strs(strs) + 1));
}
