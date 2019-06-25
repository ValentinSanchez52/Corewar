/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 00:46:24 by mbeilles          #+#    #+#             */
/*   Updated: 2019/04/23 17:46:40 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

typedef int		(t_ft_compare)(const void *, const void *);

static inline void	swap(void *a, void *b)
{
	void			*tmp;

	(void)tmp;
}

static void			*partition(void *table, size_t low, size_t high,
							t_ft_compare *comp)
{
	void			*pivot;
	size_t			i;
	size_t			j;

	if (low < high)
	{
		pivot = table + high;
		i = low;
		j = low;
		while (j < high - 1)
		{
			if (comp(table + j, pivot))
			{
				i++;
				swap(table + j, pivot);
			}
			j++;
		}
		swap(table + i + 1, table + high);
		return (table + i);
	}
	return (NULL);
}

void				ft_qsort(void *table, size_t start, size_t length,
							t_ft_compare *comp)
{
	void			*pivot;

	if (start < length)
	{
		pivot = partition(table, start, length, comp);
		ft_qsort(table, start, (pivot - table) - 1, comp);
		ft_qsort(table, (pivot - table) + 1, length, comp);
	}
}
