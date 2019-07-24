/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 12:04:05 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/24 12:11:40 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				run_process_cleaner(
		t_vm *vm
)
{
	t_process		*process;
	uint64_t		i;

	i = 0;
	while ((process = ft_dynarray_iterate(&vm->process, &i,
					sizeof(t_process))))
		if (!process->living)
		{
			ft_dynarray_remove(&vm->process,
					(uint8_t*)process - vm->process.array, sizeof(t_process));
			--i;
		}
}
