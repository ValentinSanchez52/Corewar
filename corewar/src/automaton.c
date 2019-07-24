/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automaton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:55:44 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/24 11:58:53 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Updates the vm's internal counters to know when to kill process that didn't
** 		live'd soon enough.
*/

static inline void	automaton_update_counters(t_vm *vm)
{
	if (vm->cycles_counter >= vm->cycles_to_die)
	{
		if (vm->live_counter >= COR_CYCLES_LIVES || !vm->cycles_left)
		{
			run_process_cleaner(vm);
			vm->cycles_left = COR_CYCLES_LEFT;
			vm->cycles_counter = 0;
			vm->live_counter = 0;
		}
		else if (vm->live_counter < COR_CYCLES_LIVES)
			--vm->cycles_left;
	}
	else
	{
		++vm->cycles_counter;
		++vm->cycles;
	}
}

/*
** Runs the automaton on the arena with the list of process created.
** 		Runs the new process' instruction if it's not waiting for the last
** 		instruction completion.
**
** Then it updates the vm's internal counters to wipe dead processes.
*/

void				automaton_run(t_vm *vm)
{
	t_process		*process;
	t_op			*instruction;
	uint64_t		i;

	while (vm->cycles_to_die <= COR_CYCLES_DEFAULT)
	{
		i = 0;
		while ((process = ft_dynarray_iterate(&vm->process, &i,
						sizeof(t_process))))
			if (!process->waiting)
				run_process_frame(vm, process);
		i = 0;
		while ((instruction = ft_dynarray_iterate(&vm->instructions, &i,
						sizeof(t_op))))
			if (instruction->timeout > 0)
				--instruction->timeout;
			else
			{
				run_instruction_frame(vm, instruction);
				--i;
			}
		automaton_update_counters(vm);
	}
}
