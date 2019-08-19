/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:17:28 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/10 18:48:16 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "parsing.h"

/*
** - if (Check instruction validity on memory)
** - 	Get instruction
** - 	Insert instruction at 0
** - 	inc process pc to instruction size
** - else
** - 	inc process pc
*/

inline void				run_process_frame(
		t_vm *vm,
		t_process *process
)
{
	uint32_t			instruction_address;
	t_op				op;

	instruction_address = process->global_offset + process->pc;
	if (is_instruction_valid_from_arena(instruction_address))
	{
		/*printf("Exec op\n");*/
		process->op = get_instruction_from_arena(process, instruction_address);
		process->op.physical_size = get_instruction_size(&process->op);
		process->waiting = true;
		/*print_op(process, true);*/
		return ;
	}
	else if (instruction_address > 0 && instruction_address <= COR_OP_MAX)
	{
		/*printf("Op invalid -> %d\n", 1 + g_op_check[instruction_address].encoding);*/
		process->pc += 1 + g_op_check[instruction_address].encoding;
	}
	else
	{
		/*printf("No op %s\n", process->uuid);*/
		++process->pc;
	}
}
