/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 16:33:41 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/08 16:36:35 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "print.h"

void			print_processes(t_vm *vm)
{
	t_process	*proc;
	uint64_t	i;

	i = 0;
	write(1, "==================[ Proccesses ]==================\n", 51);
	while ((proc = ft_dynarray_iterate(&vm->process, &i, sizeof(t_process))))
		print_process(proc, true);
	write(1, "=====================[ End ]======================\n", 51);
}
