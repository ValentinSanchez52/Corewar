/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automaton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 17:55:44 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/08 15:56:54 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "print.h"

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
			printf("Cleaning processes...\n");
			run_process_cleaner(vm);
			vm->cycles_left = COR_CYCLES_LEFT;
			vm->cycles_counter = 0;
			vm->live_counter = 0;
			vm->cycles_to_die -= COR_CYCLES_DELTA;
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

static inline void	debug_automaton_states(t_vm *vm)
{
	char*			nums[3];

	nums[0] = ft_strdup(ft_ultostr(vm->cycles, 10, true));
	nums[1] = ft_strdup(ft_ultostr(vm->cycles_to_die, 10, true));
	nums[2] = ft_strdup(ft_ultostr(COR_CYCLES_DELTA, 10, true));
	print((t_print){
			.data = ft_strajoin(7, "Stack frame: [\e[34mC: ",
					nums[0], "\e[0m] [\e[31mCtd: ",
					nums[1], "\e[0m] [\e[32mCd:", nums[2], "\e[0m]\n"),
			.printer = printer,
			.destructor = &free
	});
	ft_afree(3, nums[0], nums[1], nums[2]);
}

/*
** Runs the automaton on the arena with the list of process created.
** 		Runs the new process' instruction if it's not waiting for the last
** 		instruction completion.
**
** Then it updates the vm's internal counters to wipe dead processes.
*/

#include <stdio.h>
void				automaton_run(t_vm *vm)
{
	t_process		*process;
	t_op			*instruction;
	uint64_t		i;

	while (vm->cycles_to_die <= COR_CYCLES_DEFAULT
			&& !(vm->flags.dump && vm->flags.dump_cycle < vm->cycles))
	{
		i = 0;
		while ((process = ft_dynarray_iterate(&vm->process, &i,
						sizeof(t_process))))
			if (!process->waiting)
			{
				/* print_process(process, true); */
				run_process_frame(vm, process);
			}
			else if (process->op.timeout > 0)
				--process->op.timeout;
			else
			{
				print_op(process, true);
				/* print_process(process, true); */
				run_instruction_frame(vm, process);
			}
		automaton_update_counters(vm);
	}
}
