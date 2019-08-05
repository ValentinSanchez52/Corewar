/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 19:30:46 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/05 17:00:53 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "corewar.h"

static const char	*g_op_names[COR_OP_MAX] = {
	[0] = "WTF?",
	[COR_OP_LIVE] = "\e[1;31mLive <3\e[0m",
	[COR_OP_LOAD] = "\e[1;33mLoad\e[0m",
	[COR_OP_STORE] = "\e[1;32mStore\e[0m",
	[COR_OP_ADD] = "\e[1;34mAdd \e[0;32m+\e[0m",
	[COR_OP_SUB] = "\e[1;34mSub \e[0;31m-\e[0m",
	[COR_OP_AND] = "\e[1;34mAnd \e[0;34m&\e[0m",
	[COR_OP_OR] = "\e[1;34mOr \e[0;35m|\e[0m",
	[COR_OP_XOR] = "\e[1;34mXor \e[0;35m^\e[0m",
	[COR_OP_ZJUMP] = "\e[1;35mZjump\e[0m",
	[COR_OP_LOAD_IDX] = "\e[1;33mLoad\e[0;33m index\e[0m",
	[COR_OP_STORE_IDX] = "\e[1;32mStore \e[0;32mindex\e[0m",
	[COR_OP_FORK] = "\e[1;36mFork\[0m",
	[COR_OP_LONG_LOAD] = "\e[33mLong \e[1mload\e[0m",
	[COR_OP_LONG_LOAD_IDX] = "\e[33mLong \e[1mload\e[0;33m index\e[0m",
	[COR_OP_LONG_FORK] = "\e[36mLong \e[1mfork\e[0m",
	[COR_OP_AFF] = "\e[1;34mAff\e[0m",
};

static const char	*g_op_arg_names[COR_ARG_MAX] = {
	[COR_ARG_DIR] = "\e[34mDirect\e[0m:",
	[COR_ARG_IND] = "\e[33mIndirect\e[0m:",
	[COR_ARG_REG] = "\e[32mRegister\e[0m:",
};

void				print_op(t_op *op)
{
	t_dynarray		msg;
	uint32_t		i;

	msg = ft_dynarray_create_loc(4096, 1 << 20);
	ft_dynarray_push_str(&msg, "[0x");
	ft_dynarray_push_str(&msg, ft_ultostr((uint64_t)op->process, 16, false));
	ft_dynarray_push_str(&msg, "] ");
	ft_dynarray_push_str(&msg, "[");
	ft_dynarray_push_str(&msg, (void*)g_op_names[op->code]);
	ft_dynarray_push_str(&msg, "] ");
	i = 0;
	while (i < op->param_count)
	{
		ft_dynarray_push_str(&msg, "[");
		ft_dynarray_push_str(&msg, (void*)g_op_arg_names[op->types[i]]);
		ft_dynarray_push_str(&msg, "\e[33m0x");
		ft_dynarray_push_str(&msg, ft_ultostr(op->args[i], 16, false));
		ft_dynarray_push_str(&msg, "\e[0m]");
		i++;
	}
	ft_dynarray_push_str(&msg, " Remain: ");
	ft_dynarray_push_str(&msg, ft_ultostr(op->timeout, 10, true));
	ft_dynarray_push(&msg, " cycles.\n", 10);
	print((t_print){.data = msg.array, .printer = printer, .destructor = free});
}
