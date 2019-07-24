/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:17:28 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/24 12:03:39 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** - if (Check instruction validity on memory)
** - 	exec
** - 	Insert instruction at 0
** - 	inc process pc to instruction size
** - else
** - 	inc process pc
*/

static const t_op_check	g_op_check[COR_OP_MAX] = {
	[COR_OP_LIVE] = {
		.len = 1, .args = {COR_T_DIR},
	},
	[COR_OP_ZJUMP] = {
		.len = 1, .args = {COR_T_DIR},
	},
	[COR_OP_FORK] = {
		.len = 1, .args = {COR_T_DIR},
	},
	[COR_OP_LONG_FORK] = {
		.len = 1, .args = {COR_T_DIR},
	},
	[COR_OP_AFF] = {
		.len = 1, .args = {COR_T_REG},
	},
	[COR_OP_LOAD] = {
		.len = 2, .args = {
			COR_T_IND | COR_T_DIR,
			COR_T_REG
		},
	},
	[COR_OP_LONG_LOAD] = {
		.len = 2, .args = {
			COR_T_DIR | COR_T_IND,
			COR_T_REG
		},
	},
	[COR_OP_ADD] = {
		.len = 3, .args = {
			COR_T_REG,
			COR_T_REG,
			COR_T_REG
		},
	},
	[COR_OP_SUB] = {
		.len = 3, .args = {
			COR_T_REG,
			COR_T_REG,
			COR_T_REG
		},
	},
	[COR_OP_AND] = {
		.len = 3, .args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG
		},
	},
	[COR_OP_OR] = {
		.len = 3, .args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG
		},
	},
	[COR_OP_XOR] = {
		.len = 3, .args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG
		},
	},
	[COR_OP_LOAD_IDX] = {
		.len = 3, .args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_DIR | COR_T_REG,
			COR_T_REG
		},
	},
	[COR_OP_STORE_IDX] = {
		.len = 3, .args = {
			COR_T_REG,
			COR_T_REG | COR_T_DIR | COR_T_IND,
			COR_T_DIR | COR_T_REG
		},
	},
	[COR_OP_LONG_LOAD_IDX] = {
		.len = 3, .args = {
			COR_T_REG| COR_T_IND | COR_T_DIR,
			COR_T_DIR | COR_T_REG,
			COR_T_REG
		},
	},
};

static inline bool		is_valid_instruction(uint8_t *memory)
{
	if (!*memory || *memory >= COR_OP_MAX)
		return (false);
	// Further check
	return (true);
}

static inline t_op		get_instruction(
		uint8_t *memory
)
{
	return ((t_op){});
}

inline void				run_process_frame(
		t_vm *vm,
		t_process *process
)
{
	uint8_t				*instruction_address;
	t_op				op;

	instruction_address = vm->arena + process->global_offset + process->pc;
	if (is_valid_instruction(instruction_address))
	{
		op = get_instruction(instruction_address);
		ft_dynarray_insert(&vm->instructions, 0, &op, sizeof(t_op));
		process->waiting = true;
	}
	else
		++process->pc;
}
