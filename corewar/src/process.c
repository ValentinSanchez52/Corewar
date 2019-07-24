/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:17:28 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/24 18:06:50 by mbeilles         ###   ########.fr       */
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
		.count = 1,
		.cycles = 10,
		.args = {COR_T_DIR},
	},
	[COR_OP_ZJUMP] = {
		.count = 1,
		.cycles = 20,
		.args = {COR_T_DIR},
	},
	[COR_OP_FORK] = {
		.count = 1,
		.cycles = 800,
		.args = {COR_T_DIR},
	},
	[COR_OP_LONG_FORK] = {
		.count = 1,
		.cycles = 1000,
		.args = {COR_T_DIR},
	},
	[COR_OP_AFF] = {
		.count = 1,
		.cycles = 2,
		.encoding = true,
		.args = {COR_T_REG},
	},
	[COR_OP_LOAD] = {
		.count = 2,
		.cycles = 5,
		.encoding = true,
		.args = {
			COR_T_IND | COR_T_DIR,
			COR_T_REG
		},
	},
	[COR_OP_LONG_LOAD] = {
		.count = 2,
		.cycles = 10,
		.encoding = true,
		.args = {
			COR_T_DIR | COR_T_IND,
			COR_T_REG
		},
	},
	[COR_OP_ADD] = {
		.count = 3,
		.cycles = 10,
		.encoding = true,
		.args = {
			COR_T_REG,
			COR_T_REG,
			COR_T_REG
		},
	},
	[COR_OP_SUB] = {
		.count = 3,
		.cycles = 10,
		.encoding = true,
		.args = {
			COR_T_REG,
			COR_T_REG,
			COR_T_REG
		},
	},
	[COR_OP_AND] = {
		.count = 3,
		.cycles = 6,
		.encoding = true,
		.args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG
		},
	},
	[COR_OP_OR] = {
		.count = 3,
		.cycles = 6,
		.encoding = true,
		.args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG
		},
	},
	[COR_OP_XOR] = {
		.count = 3,
		.cycles = 6,
		.encoding = true,
		.args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_REG
		},
	},
	[COR_OP_LOAD_IDX] = {
		.count = 3,
		.cycles = 25,
		.encoding = true,
		.args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_DIR | COR_T_REG,
			COR_T_REG
		},
	},
	[COR_OP_STORE_IDX] = {
		.count = 3,
		.cycles = 25,
		.encoding = true,
		.args = {
			COR_T_REG,
			COR_T_REG | COR_T_DIR | COR_T_IND,
			COR_T_DIR | COR_T_REG
		},
	},
	[COR_OP_LONG_LOAD_IDX] = {
		.count = 3,
		.cycles = 50,
		.encoding = true,
		.args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_DIR | COR_T_REG,
			COR_T_REG
		},
	},
};

static const uint8_t	g_op_arg_code_size[COR_ARG_MAX] = {
	[COR_ARG_REG] = COR_ARG_SIZ_REG,
	[COR_ARG_DIR] = COR_ARG_SIZ_DIR,
	[COR_ARG_IND] = COR_ARG_SIZ_IND,
};

/*
** Check if opcode is valid
**
** And if there is an encoding byte for the instruction,
** 		check argument type validity.
**
** 		arg type:1, 2, 3, 4.
** 		encode :[aa bb cc dd]
** 		              &
** 		i = 1  :[11 00 00 00] >> 1 |=> aa
** 		i = 2  :[00 11 00 00] >> 2 |=> bb
** 		i = 3  :[00 00 11 00] >> 3 |=> cc
** 		i = 4  :[00 00 00 11] >> 4 |=> dd
**
**		And then copares each argument to the expected ones.
*/

static inline t_op_type	get_arg_type(uint8_t encode, uint32_t i)
{
	return (1 << (((encode & (0b11 << (COR_ARG_NUMBER_MAX - i))) >> i) - 1));
}

static inline uint32_t	get_arg_value(
		uint8_t *memory,
		t_op_arg_code *types,
		uint32_t index
)
{
	uint32_t			i;

	i = 0;
	while (i < index)
	{
		memory += g_op_arg_code_size[i];
		++i;
	}
	++memory;
	return (*((uint32_t*)memory)
			& (0xFFFFFFFF << ((4 - g_op_arg_code_size[i]) * 8)));
}

static inline t_op		get_instruction(
		t_process *process,
		uint8_t *memory
)
{
	uint32_t			args[COR_ARG_NUMBER_MAX];
	t_op_arg_code		types[COR_ARG_NUMBER_MAX];
	t_op_check			properties;
	uint8_t				encode;
	uint32_t			i;

	encode = memory[1];
	i = 0;
	while (i < properties.count)
	{
		types[i] = ((get_arg_type(encode, i)) >> 1) + 1;
		args[i] = get_arg_value(memory, types, i);
		i++;
	}
	properties = g_op_check[*memory];
	return ((t_op){
			.code = *memory,
			.param_count = properties.count,
			.timeout = properties.cycles,
			.process = process,
			.types = {types[0], types[1], types[2], types[3]},
			.args = {args[0], args[1], args[2], args[3]},
	});
}

static inline bool		is_valid_instruction(uint8_t *memory)
{
	uint8_t				encode;
	uint8_t				i;

	if (!*memory || *memory >= COR_OP_MAX)
		return (false);
	if (g_op_check[*memory].encoding)
	{
		encode = memory[1];
		i = 0xff;
		while (++i < g_op_check[*memory].count)
			if (!(get_arg_type(encode, i) & g_op_check[*memory].args[i]))
				return (false);
	}
	return (true);
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
		op = get_instruction(process, instruction_address);
		ft_dynarray_insert(&vm->instructions, 0, &op, sizeof(t_op));
		process->waiting = true;
	}
	else
		++process->pc;
}
