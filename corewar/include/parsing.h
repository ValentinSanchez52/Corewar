/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:57:06 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/05 20:35:33 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "corewar.h"

/*
** =============================================================================
** 		Operation integrity verification struct
** =============================================================================
*/

typedef struct		s_op_check
{
	uint8_t			count;
	uint32_t		cycles;
	t_op_type		args[COR_ARG_NUMBER_MAX];
	t_op_arg_code	default_types[COR_ARG_NUMBER_MAX];
	bool			encoding : 1;
	bool			dir_addr : 1;
}					t_op_check;

/*
** =============================================================================
** 		Global checking instruction integrity
** =============================================================================
*/

static const t_op_check	g_op_check[COR_OP_MAX] = {
	[COR_OP_LIVE] = {
		.count = 1,
		.cycles = 10,
		.default_types = {COR_ARG_DIR},
		.args = {COR_T_DIR},
	},
	[COR_OP_ZJUMP] = {
		.count = 1,
		.cycles = 20,
		.dir_addr = true,
		.default_types = {COR_ARG_DIR},
		.args = {COR_T_DIR},
	},
	[COR_OP_FORK] = {
		.count = 1,
		.cycles = 800,
		.dir_addr = true,
		.default_types = {COR_ARG_DIR},
		.args = {COR_T_DIR},
	},
	[COR_OP_LONG_FORK] = {
		.count = 1,
		.cycles = 1000,
		.dir_addr = true,
		.default_types = {COR_ARG_DIR},
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
			COR_T_REG,
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
		.dir_addr = true,
		.encoding = true,
		.args = {
			COR_T_REG | COR_T_IND | COR_T_DIR,
			COR_T_DIR | COR_T_REG,
			COR_T_REG
		},
	},
	[COR_OP_STORE] = {
		.count = 2,
		.cycles = 5,
		.encoding = true,
		.args = {
			COR_T_REG,
			COR_T_IND | COR_T_DIR,
		},
	},
	[COR_OP_STORE_IDX] = {
		.count = 3,
		.cycles = 25,
		.dir_addr = true,
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
		.dir_addr = true,
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

#endif
