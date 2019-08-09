/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_spawner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njiall </var/spool/mail/njiall>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 21:08:00 by njiall            #+#    #+#             */
/*   Updated: 2019/08/09 21:38:26 by njiall           ###   ########.fr       */
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
