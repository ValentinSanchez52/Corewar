/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:17:28 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/20 11:43:40 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "parsing.h"

/*
** - if (Check instruction validity on memory)
** - 	Get instruction
** - 	Insert instruction at 0
** - 	inc proc pc to instruction size
** - else
** - 	inc proc pc
*/

inline void				run_process_frame(
		t_vm *vm,
		t_process *proc
)
{
	uint32_t			instruction_address;
	uint8_t				cell;

	instruction_address = proc->global_offset + proc->pc;
	cell = get_mem_value(instruction_address, 1);
	if (is_instruction_valid_from_arena(instruction_address))
	{
		proc->op = get_instruction_from_arena(proc, instruction_address);
		proc->op.physical_size = get_instruction_size(&proc->op);
		proc->waiting = true;
		return ;
	}
	else if (cell > 0 && cell <= COR_OP_MAX)
		proc->pc += 1 + g_op_check[cell].encoding;
	else
		++proc->pc;
}
