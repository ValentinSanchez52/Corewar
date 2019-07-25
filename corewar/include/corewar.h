/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:03:56 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/25 18:56:39 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdint.h>
# include <stdbool.h>
# include "dynarray.h"
# include "bboa.h"
# include "libft.h"
# include "dynarray.h"

/*
** Struct for ease of use for Libboa.
*/

typedef enum		e_option_type
{
	OPT_NONE,
	OPT_DOUBLE,
	OPT_SINGLE,
	OPT_MAX
}					t_option_type;

typedef struct		s_option
{
	char			*option[16];
	t_option_type	type[16];
	uint32_t		length;
	t_opt_match		match;
}					t_option;

/*
** =============================================================================
**
** 		Data structure for corewar's vm.
**
** =============================================================================
*/

# define			COR_ARENA_SIZE			(1 << 12) // 4096
# define			COR_CYCLES_DEFAULT		(1536) // Default value for cycles_to_die
# define			COR_CYCLES_DELTA		(50) // Delta decrease cycles_to_die
# define			COR_CYCLES_LIVES		(21)
# define			COR_CYCLES_LEFT			(10)
# define			COR_ARG_NUMBER_MAX		(4)
# define			COR_WARRIOR_NB_MAX		(4)
# define			COR_IDX_MOD				(COR_ARENA_SIZE / 8)
# define			COR_REG_SIZE			(4)

# define			WARRIOR_DEFAULT_MAGIC	(0x00ea83f3)
# define			WARRIOR_MAGIC			(4)
# define			WARRIOR_NAME			(128)
# define			WARRIOR_PADDING			(4)
# define			WARRIOR_SIZE			(4)
# define			WARRIOR_COMMENT			(2048)
# define			WARRIOR_MAX_SIZE		(COR_ARENA_SIZE/6)

/*
** =============================================================================
** 		Operations
** =============================================================================
** 		Default building blocks
** =============================================================================
*/

typedef enum		e_op_code
{
	COR_OP_LIVE = 1,
	COR_OP_LOAD,
	COR_OP_STORE,
	COR_OP_ADD,
	COR_OP_SUB,
	COR_OP_AND,
	COR_OP_OR,
	COR_OP_XOR,
	COR_OP_ZJUMP,
	COR_OP_LOAD_IDX,
	COR_OP_STORE_IDX,
	COR_OP_FORK,
	COR_OP_LONG_LOAD,
	COR_OP_LONG_LOAD_IDX,
	COR_OP_LONG_FORK,
	COR_OP_AFF,
	COR_OP_MAX
}					t_op_code;

typedef enum		e_op_arg_code
{
	COR_ARG_REG = 1,
	COR_ARG_DIR,
	COR_ARG_IND,
	COR_ARG_MAX
}					t_op_arg_code;

typedef enum		e_op_type
{
	COR_T_NONE,
	COR_T_REG = 1 << (COR_ARG_REG - 1),
	COR_T_DIR = 1 << (COR_ARG_DIR - 1),
	COR_T_IND = 1 << (COR_ARG_IND - 1),
}					t_op_type;

typedef enum		e_op_arg_size
{
	COR_ARG_SIZ_IND = 2,
	COR_ARG_SIZ_REG = 4,
	COR_ARG_SIZ_DIR = 4,
}					t_op_arg_size;

/*
** =============================================================================
** 		Operation intergrity verification struct
** =============================================================================
*/

typedef struct		s_op_check
{
	uint8_t			count;
	uint32_t		cycles;
	t_op_type		args[COR_ARG_NUMBER_MAX];
	bool			encoding : 1;
}					t_op_check;

/*
** =============================================================================
** 		Processes
** =============================================================================
*/

typedef struct		s_process
{
	uint32_t		registers[16];
	uint32_t		pc : 12; // 12 bit counter
	uint32_t		global_offset;
	bool			carry : 1;
	bool			living : 1;
	bool			waiting : 1;
}					t_process;

/*
** =============================================================================
** 		Operation struct
** =============================================================================
*/

typedef struct		s_op
{
	t_op_code		code;
	uint32_t		timeout;
	uint32_t		param_count; // Should be <= COR_ARG_NUMBER_MAX
	t_op_arg_code	types[COR_ARG_NUMBER_MAX];
	uint32_t		args[COR_ARG_NUMBER_MAX];
	t_process		*process;
}					t_op;

/*
** =============================================================================
** 		Warriors
** =============================================================================
*/

typedef enum		e_arena_own
{
	COR_ARN_NO_CLAIM,
	COR_ARN_W1_CLAIM,
	COR_ARN_W2_CLAIM,
	COR_ARN_W3_CLAIM,
	COR_ARN_W4_CLAIM,
	COR_ARN_MAX
}					t_arena_own;

typedef struct		s_warrior
{
	uint32_t		id;
	char			name[WARRIOR_NAME + 1];
	char			comment[WARRIOR_COMMENT + 1];
	uint8_t			assembly[WARRIOR_MAX_SIZE + 1];
	uint32_t		assembly_size;
	uint32_t		cycle_last;
	uint32_t		magic;
	bool			living: 1;
}					t_warrior;

/*
** =============================================================================
** 		Vm
** =============================================================================
*/

typedef struct		s_vm
{
	uint8_t			arena[COR_ARENA_SIZE];
	t_arena_own		arena_claim[COR_ARENA_SIZE];
	uint32_t		cycles_to_die; // First clean limit
	uint32_t		cycles_counter; // Counts cycles up to cycles_to_die
	uint32_t		cycles_left; // Cycles until forced clean
	uint32_t		cycles; // Cycles passed so far
	uint32_t		live_counter; // Number of lives inside a cycles_to_die
	t_warrior		warriors[4];
	uint32_t		warriors_nb;
	t_dynarray		process;
	t_dynarray		instructions;
}					t_vm;

extern t_vm			vm;

/*
** =============================================================================
** 		Functions
** =============================================================================
*/

void				run_instruction_frame(t_vm *vm, t_op *instruction);
void				run_process_frame(t_vm *vm, t_process *process);
void				run_process_cleaner(t_vm *vm);

uint32_t			get_mem_value(uint32_t index, uint32_t size);
uint8_t				get_mem_cell(uint32_t index);
void				reg_set_value(t_process *process, uint8_t reg_id,
		uint32_t value);
uint32_t			get_reg_value(t_process *process, uint8_t reg_id);
uint32_t			*get_register(t_process *process, uint8_t reg_id);

void				print_warriors(void);
void				print_arena(void);
uint32_t			macos_flip_bytes(uint32_t n);
void				corewar_load_warriors(int c, char *file);
void				corewar_load_arena(void);

#endif
