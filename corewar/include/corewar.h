/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:03:56 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/23 18:58:27 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdint.h>
# include <stdbool.h>
# include "dynarray.h"
# include "bboa.h"

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

# define			COR_NAME_LENGTH			(128)
# define			COR_COMMENT_LENGTH		(2048)
# define			COR_EXEC_MAGIC			(0xea83f3)
# define			COR_MAGIC_SIZE			(4)

# define			COR_ARENA_SIZE			(1 << 12) // 4096
# define			COR_WARRIOR_SIZE		(COR_ARENA_SIZE / 6)
# define			COR_CYCLES_DEFAULT		(1536) // Default value for cycles_to_die
# define			COR_CYCLES_DELTA		(50) // Delta decrease cycles_to_die
# define			COR_CYCLES_LIVES		(21)
# define			COR_CYCLES_LEFT			(10)

/*
** =============================================================================
** 		Operations
** =============================================================================
*/

typedef union		u_op
{
	t_op_code		code;
	t_op_default	dflt_op; // T_DIR
	t_op_logic		lgic_op; // T_REG,  T_REG,  T_REG
	t_op_bitwise	btws_op; // T_REG | T_IND | T_DIR,  T_REG | T_IND | T_DIR, T_REG
	t_op_load		load_op; // T_IND | T_DIR,  T_REG
	t_op_lindex		lidx_op; // T_REG | T_IND | T_DIR,  T_DIR | T_REG,  T_REG
	t_op_sindex		sidx_op; // T_REG,  T_REG | T_DIR | T_IND,  T_DIR | T_REG
}					t_op;

/*
** =============================================================================
** 		Processes
** =============================================================================
*/

typedef struct		s_process
{
	uint32_t		registers[16];
	uint32_t		pc : 12; // 12 bit counter
	uint8_t			id : 4;
	bool			carry : 1;
	bool			living : 1;
	bool			waiting : 1;
}					t_process;

typedef struct		s_instruction
{
	t_process		*process;
	uint32_t		timeout;
	t_op			op;
}					t_instruction;

/*
** =============================================================================
** 		Warriors
** =============================================================================
*/

typedef struct		s_warrior
{
	char			name[COR_NAME_LENGTH];
	char			comment[COR_COMMENT_LENGTH];
	uint8_t			*assembly;
	uint32_t		assembly_size;
	uint32_t		cycle_last;
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
	uint32_t		cycles_to_die; // First clean limit
	uint32_t		cycles_left; // Cycles until forced clean
	uint32_t		cycles_counter; // Counts cycles up to cycles_to_die
	uint32_t		cycles; // Cycles passed so far
	uint32_t		live_counter; // Number of lives inside a cycles_to_die
	t_warrior		warriors[4];
	t_dynarray		process;
	t_dynarray		instructions;
}					t_vm;

extern t_vm			vm;

#endif
