/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:20:20 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/10 16:51:40 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					op_fork(t_process *proc)
{
	t_process			new_process;

	new_process = *(proc);
	new_process.global_offset = (proc->pc + (uint16_t)proc->op.args[0])
		& (COR_ARENA_SIZE - 1);
	new_process.pc = 0;
	new_process.waiting = false;
	new_process.living = false;
	new_process.op = (t_op){};
	str_uuid_generate(new_process.uuid);
	ft_dynarray_push(&(g_vm.process_queue), &new_process, sizeof(t_process));
}
