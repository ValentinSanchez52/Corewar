/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 07:38:46 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/10 17:35:40 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "dynarray.h"
#include "corewar.h"
#include "print.h"

static const char * const	g_claim_col[COR_ARN_MAX] = {
	[COR_ARN_NO_CLAIM] = "\e[37m",
	[COR_ARN_W1_CLAIM] = "\e[1;34m",
	[COR_ARN_W2_CLAIM] = "\e[1;33m",
	[COR_ARN_W3_CLAIM] = "\e[1;32m",
	[COR_ARN_W4_CLAIM] = "\e[1;31m",
};

static inline void	append_dump_index(t_dynarray *msg, uint32_t index)
{
	char			*number;
	size_t			len;

	number = ft_ultostr(index, 16, false);
	len = ft_strlen(number);
	ft_dynarray_push(msg, "\033[38;5;130m0x\033[38;5;166m0000", 24 + (4 - len));
	ft_dynarray_push_str(msg, number);
	ft_dynarray_push(msg, "\e[0m: ", 6);
}

static inline void	print_dump_32(t_vm *vm)
{
	t_dynarray		msg;
	uint32_t		i;

	msg = ft_dynarray_create_loc(0, 0);
	i = 0;
	while (i < sizeof(vm->arena) / sizeof(uint8_t))
	{
		if ((i & 31) == 0 && i != 0)
			ft_dynarray_push(&msg, "\n", 1);
		if ((i & 31) == 0)
			append_dump_index(&msg, i);
		if (vm->arena_claim[i] < COR_ARN_MAX)
			ft_dynarray_push_str(&msg, (void*)g_claim_col[vm->arena_claim[i]]);
		else
			ft_dynarray_push_str(&msg, (void*)g_claim_col[COR_ARN_NO_CLAIM]);
		if (vm->arena[i] <= 0xf)
			ft_dynarray_push(&msg, "0", 1);
		ft_dynarray_push_str(&msg, ft_ultostr(vm->arena[i], 16, false));
		ft_dynarray_push_str(&msg, "\e[0m");
		if ((i & 31) != 31)
			ft_dynarray_push(&msg, " ", 1);
		i++;
	}
	ft_dynarray_push(&msg, "\n", 1);
	write(1, msg.array, msg.index);
	ft_dynarray_destroy(&msg, false);
}

static inline void	print_dump_64(t_vm *vm)
{
	t_dynarray		msg;
	uint32_t		i;

	msg = ft_dynarray_create_loc(0, 0);
	i = 0;
	while (i < sizeof(vm->arena) / sizeof(uint8_t))
	{
		if ((i & 63) == 0 && i != 0)
			ft_dynarray_push(&msg, "\n", 1);
		if ((i & 63) == 0)
			append_dump_index(&msg, i);
		if (vm->arena_claim[i] < COR_ARN_MAX)
			ft_dynarray_push_str(&msg, (void*)g_claim_col[vm->arena_claim[i]]);
		else
			ft_dynarray_push_str(&msg, (void*)g_claim_col[COR_ARN_NO_CLAIM]);
		if (vm->arena[i] <= 0xf)
			ft_dynarray_push(&msg, "0", 1);
		ft_dynarray_push_str(&msg, ft_ultostr(vm->arena[i], 16, false));
		ft_dynarray_push_str(&msg, "\e[0m");
		if ((i & 63) != 63)
			ft_dynarray_push(&msg, " ", 1);
		i++;
	}
	ft_dynarray_push(&msg, "\n", 1);
	write(1, msg.array, msg.index);
	ft_dynarray_destroy(&msg, false);
}

static inline void	print_dump_128(t_vm *vm)
{
	t_dynarray		msg;
	uint32_t		i;

	msg = ft_dynarray_create_loc(0, 0);
	i = 0;
	while (i < sizeof(vm->arena) / sizeof(uint8_t))
	{
		if ((i & 127) == 0 && i != 0)
			ft_dynarray_push(&msg, "\n", 1);
		if ((i & 127) == 0)
			append_dump_index(&msg, i);
		if (vm->arena_claim[i] < COR_ARN_MAX)
			ft_dynarray_push_str(&msg, (void*)g_claim_col[vm->arena_claim[i]]);
		else
			ft_dynarray_push_str(&msg, (void*)g_claim_col[COR_ARN_NO_CLAIM]);
		if (vm->arena[i] <= 0xf)
			ft_dynarray_push(&msg, "0", 1);
		ft_dynarray_push_str(&msg, ft_ultostr(vm->arena[i], 16, false));
		ft_dynarray_push_str(&msg, "\e[0m");
		if ((i & 127) != 127)
			ft_dynarray_push(&msg, " ", 1);
		i++;
	}
	ft_dynarray_push(&msg, "\n", 1);
	write(1, msg.array, msg.index);
	ft_dynarray_destroy(&msg, false);
}

void				print_dump(t_vm *vm)
{
	if (vm->flags.dump_size == DMP_SIZE_32)
		print_dump_32(vm);
	else if (vm->flags.dump_size == DMP_SIZE_64)
		print_dump_64(vm);
	else if (vm->flags.dump_size == DMP_SIZE_128)
		print_dump_128(vm);
}
