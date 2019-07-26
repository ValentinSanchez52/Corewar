/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:36:34 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/26 06:43:06 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "print.h"

void				print_process(t_process *proc)
{
	t_dynarray		msg;
	uint32_t		i;

	msg = ft_dynarray_create_loc(4096, 1 << 20);
	ft_dynarray_push_str(&msg, "[Go:0x");
	ft_dynarray_push_str(&msg, ft_ultostr(proc->global_offset, 16, false));
	ft_dynarray_push_str(&msg, "] + [Pc:0x");
	ft_dynarray_push_str(&msg, ft_ultostr(proc->pc, 16, false));
	ft_dynarray_push_str(&msg, "] ");
	i = 0;
	while (i < 16)
	{
		ft_dynarray_push_str(&msg, "[r");
		ft_dynarray_push_str(&msg, ft_ultostr(i, 16, false));
		ft_dynarray_push_str(&msg, ":\e[34m0x");
		ft_dynarray_push_str(&msg, ft_ultostr(proc->registers, 16, false));
		ft_dynarray_push_str(&msg, "\e[0m]");
		i++;
	}
	ft_dynarray_push_str(&msg, proc->carry ? "[Carry: \e[32mtrue\e[0m] "
			: "[Carry: \e[35mfalse\e[0m] ");
	ft_dynarray_push_str(&msg, proc->living ? "Alive" : "Dying");
	ft_dynarray_push_str(&msg, proc->waiting ? "Executing..." : "Idle");
	print((t_print){.data = msg.array, .printer = printer, .destructor = free});
}
