/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 07:19:32 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/26 07:46:19 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					op_lfork(t_op *op)
{
	t_process			new_process;

	new_process = *(op->process);
	new_process.global_offset = op->process->pc + (uint16_t)op->args[0];
	new_process. pc = 0;
	ft_dynarray_push(&(vm.process), &new_process, sizeof(t_process));
}
