/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_warrior.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 16:42:32 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 19:54:33 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "print.h"

void			print_warrior(t_warrior *w, uint32_t index, bool newline)
{
	t_dynarray		msg;
	uint32_t		i;

	msg = ft_dynarray_create_loc(4096, 1 << 20);
	ft_dynarray_push_str(&msg, "Warrior [name: ");
	ft_dynarray_push_str(&msg, w->name);
	ft_dynarray_push_str(&msg, "][");
	ft_dynarray_push_str(&msg, ft_ultostr(index, 10, true));
	ft_dynarray_push_str(&msg, "] [comment: '");
	ft_dynarray_push_str(&msg, w->comment);
	ft_dynarray_push_str(&msg, "'] [weight: ");
	ft_dynarray_push_str(&msg, ft_ultostr(w->assembly_size, 16, true));
	ft_dynarray_push_str(&msg, "]");
	ft_dynarray_push(&msg, (newline ? "\n" : ""), 1 + newline);
	print_vm((t_print){
			.data = msg.array,
			.printer = printer,
			.destructor = free
	});
}
