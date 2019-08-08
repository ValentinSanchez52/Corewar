/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 09:30:45 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/08 14:10:13 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "corewar.h"

static void			(*g_ops_exec[COR_OP_MAX])(t_process *process) = {
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
		t_process *proc
)
{
	if (g_ops_exec[proc->op.code])
		g_ops_exec[proc->op.code](proc);
	proc->waiting = false;
	if (proc->op.code != COR_OP_ZJUMP)
		proc->pc += proc->op.physical_size;
	proc->op = (t_op){};
}
