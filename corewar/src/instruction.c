/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 09:30:45 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/26 09:39:42 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "corewar.h"

static const void	(*g_ops_exec[COR_OP_MAX])(t_op *op) = {
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

	[COR_OP_LIVE] = op_live,
	[COR_OP_LOAD] = op_ld,
	[COR_OP_STORE] = op_st,
	[COR_OP_ADD] = op_add,
	[COR_OP_SUB] = op_sub,
	[COR_OP_AND] = op_and,
	[COR_OP_OR] = op_or,
	[COR_OP_XOR] = op_xor,
	[COR_OP_ZJUMP] = op_zjmp,
	[COR_OP_LOAD_IDX] = op_ldi,
	[COR_OP_STORE_IDX] = op_sti,
	[COR_OP_FORK] = op_fork,
	[COR_OP_LONG_LOAD] = op_lld,
	[COR_OP_LONG_LOAD_IDX] = op_lldi,
	[COR_OP_LONG_FORK] = op_lfork,
	[COR_OP_AFF] = op_aff,
};

inline void			run_instruction_frame(
		t_vm *vm,
		t_op *op
)
{
	if (g_ops_exec[op->code])
		g_ops_exec[op->code](op);
	op->process->waiting = false;
	if (op->code != COR_OP_ZJUMP)
		op->process->pc += get_instruction_size(op);
	ft_dynarray_remove(&vm->instructions,
			(uint8_t*)op - vm->instructions.array, sizeof(t_op));
}
