/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 20:09:51 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/23 18:22:05 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNARRAY_H
# define DYNARRAY_H

# include <stdint.h>
# include <stdbool.h>

# define DYNARRAY_DEFAULT_SIZE (1u << 11u)
# define DYNARRAY_DEFAULT_MAX (1u << 23u)

typedef struct		s_dynarray {
	uint8_t			*array;
	uint64_t		index;
	uint64_t		size;
	uint64_t		max_size;
	uint64_t		min_size;
}					t_dynarray;

t_dynarray			*ft_dynarray_create(uint64_t min_size, uint64_t max_size);
t_dynarray			ft_dynarray_create_loc(uint64_t min, uint64_t max);
t_dynarray			*ft_dynarray_duplicate(t_dynarray *dyn);
t_dynarray			*ft_dynarray_resize(t_dynarray *arr, uint64_t size);
void				*ft_dynarray_push(t_dynarray *arr, void *elem,
										uint64_t size);
void				*ft_dynarray_set(t_dynarray *arr, uint64_t index,
										void *elem, uint64_t size);
void				*ft_dynarray_get(t_dynarray *arr, uint64_t index,
										uint64_t size);
void				*ft_dynarray_insert(t_dynarray *arr, uint64_t index,
										void *elem, uint64_t size);
void				*ft_dynarray_remove(t_dynarray *arr, uint64_t index,
										uint64_t size);
void				*ft_dynarray_remove_address(t_dynarray *arr, void *address,
										uint64_t size);
void				*ft_dynarray_purge(t_dynarray *arr);
void				*ft_dynarray_iterate(t_dynarray *arr, uint64_t *iter,
										uint64_t esize);
void				ft_dynarray_destroy(t_dynarray *arr, bool is_alloc);

void				*ft_dynarray_push_str(t_dynarray *arr, void *elem);

#endif
