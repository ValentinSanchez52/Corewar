/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:49:21 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 19:49:22 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				run_process_spawner(
		t_dynarray *plist,
		t_dynarray *pqueue
)
{
	if (!pqueue->index)
		return ;
	ft_dynarray_insert(plist, 0, pqueue->array, pqueue->index);
	ft_dynarray_purge(pqueue);
}
