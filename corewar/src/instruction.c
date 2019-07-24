/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 09:30:45 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/24 12:00:10 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "corewar.h"

static const void	(*g_ops_exec[COR_OP_MAX])(t_vm *vm, t_op *op) = {
	[COR_OP_LIVE] = NULL,
	[COR_OP_LOAD] = NULL,
	[COR_OP_STORE] = NULL,
	[COR_OP_ADD] = NULL,
	[COR_OP_SUB] = NULL,
	[COR_OP_AND] = NULL,
	[COR_OP_OR] = NULL,
	[COR_OP_XOR] = NULL,
	[COR_OP_ZJUMP] = NULL,
	[COR_OP_LOAD_IDX] = NULL,
	[COR_OP_STORE_IDX] = NULL,
	[COR_OP_FORK] = NULL,
	[COR_OP_LONG_LOAD] = NULL,
	[COR_OP_LONG_LOAD_IDX] = NULL,
	[COR_OP_LONG_FORK] = NULL,
};

inline void			run_instruction_frame(
		t_vm *vm,
		t_op *op
)
{
	g_ops_exec[op->code](vm, op);
	op->process->waiting = false;
	ft_dynarray_remove(&vm->instructions, (uint8_t*)op - vm->instructions.array, sizeof(t_op));
}
