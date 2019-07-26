/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 07:38:46 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/26 07:58:48 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "dynarray.h"
#include "corewar.h"

static inline void	append_dump_index(t_dynarray *msg, uint32_t index)
{
	char			*number;
	size_t			len;

	number = ft_ultostr(index, 16, false);
	len = ft_strlen(number);
	ft_dynarray_push(msg, "\e[1;34m0000", 7 + (4 - len));
	ft_dynarray_push_str(msg, number);
	ft_dynarray_push(msg, "\e[0m: ", 6);
}

void				print_dump(t_vm *vm)
{
	t_dynarray	msg;
	uint32_t	i;

	msg = ft_dynarray_create_loc(0, 0);
	i = 0;
	while (i < sizeof(vm->arena) / sizeof(uint8_t))
	{
		if ((i & 31) == 0 && i != 0)
			ft_dynarray_push(&msg, "\n", 1);
		if ((i & 31) == 0)
			append_dump_index(&msg, i);
		if (vm->arena[i] <= 0xf)
			ft_dynarray_push(&msg, "0", 1);
		ft_dynarray_push_str(&msg, ft_ultostr(vm->arena[i], 16, false));
		if ((i & 31) != 31)
			ft_dynarray_push(&msg, " ", 1);
		i++;
	}
	ft_dynarray_push(&msg, "\n", 1);
	write(1, msg.array, msg.index);
	ft_dynarray_destroy(&msg, false);
}
