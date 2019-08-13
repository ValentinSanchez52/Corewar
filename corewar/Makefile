# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/04 04:17:21 by mbeilles          #+#    #+#              #
#    Updated: 2019/08/13 16:52:40 by vsanchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#
#                                Customisation                                 #
#==============================================================================#

NAME = corewar

NICK = CWR
PROJECT_COLOR = "\033[38;5;166m"
PROJECT_COLOR_ALT = "\033[38;5;130m"

CC = clang

#==============================================================================#
#                                   Sources                                    #
#==============================================================================#

SRCS = $(PATH_SRC)/main.c													\
\
	   $(PATH_SRC)/printing/print.c											\
	   $(PATH_SRC)/printing/print_dump.c									\
	   $(PATH_SRC)/printing/print_op.c										\
	   $(PATH_SRC)/printing/print_process.c									\
	   $(PATH_SRC)/printing/print_processes.c								\
	   $(PATH_SRC)/printing/print_warrior.c									\
\
	   $(PATH_SRC)/corewar_load_arena.c										\
	   $(PATH_SRC)/corewar_load_warriors.c									\
	   $(PATH_SRC)/print_functions.c										\
\
	   $(PATH_SRC)/automaton.c												\
	   $(PATH_SRC)/instruction.c											\
	   $(PATH_SRC)/process.c												\
	   $(PATH_SRC)/process_cleaner.c										\
	   $(PATH_SRC)/process_spawner.c										\
\
	   $(PATH_SRC)/scheduler/is_instruction_valid_from_arena.c				\
	   $(PATH_SRC)/scheduler/get_instruction_from_arena.c					\
	   $(PATH_SRC)/scheduler/get_instruction_size.c							\
\
	   $(PATH_SRC)/tools/str_uuid_generate.c								\
	   $(PATH_SRC)/tools/flip_bytes.c										\
	   $(PATH_SRC)/tools/get_mem_cell.c										\
	   $(PATH_SRC)/tools/get_cell_claim.c									\
	   $(PATH_SRC)/tools/get_mem_value.c									\
	   $(PATH_SRC)/tools/set_mem_value.c									\
	   $(PATH_SRC)/tools/get_arg_type.c										\
	   $(PATH_SRC)/tools/get_arg_value.c									\
	   $(PATH_SRC)/tools/register.c											\
\
	   $(PATH_SRC)/instructions/live.c										\
	   $(PATH_SRC)/instructions/ld.c										\
	   $(PATH_SRC)/instructions/st.c										\
	   $(PATH_SRC)/instructions/add.c										\
	   $(PATH_SRC)/instructions/sub.c										\
	   $(PATH_SRC)/instructions/and.c										\
	   $(PATH_SRC)/instructions/or.c										\
	   $(PATH_SRC)/instructions/xor.c										\
	   $(PATH_SRC)/instructions/zjmp.c										\
	   $(PATH_SRC)/instructions/ldi.c										\
	   $(PATH_SRC)/instructions/sti.c										\
	   $(PATH_SRC)/instructions/fork.c										\
	   $(PATH_SRC)/instructions/lld.c										\
	   $(PATH_SRC)/instructions/lldi.c										\
	   $(PATH_SRC)/instructions/lfork.c										\
	   $(PATH_SRC)/instructions/aff.c										\
\
	   $(PATH_SRC)/ncurses/visu_cps.c										\
	   $(PATH_SRC)/ncurses/visu_borders.c									\
	   $(PATH_SRC)/ncurses/visu_legend.c									\
	   $(PATH_SRC)/ncurses/visu_state.c										\
	   $(PATH_SRC)/ncurses/visu_get_key.c									\
	   $(PATH_SRC)/ncurses/visu_clock.c										\
	   $(PATH_SRC)/ncurses/visu_cps_max.c									\
	   $(PATH_SRC)/ncurses/visu_processes.c									\
	   $(PATH_SRC)/ncurses/visu_arena.c										\
	   $(PATH_SRC)/ncurses/visu_update.c									\


INCS = $(PATH_INC)/corewar.h												\

LIBS =	\
		../libbboa \
		../libft \

SYSLIBS =	\

SYSLIBS_LINUX =	\
				uuid \

TESTS =	\
		$(PATH_TEST)/ops/ld.c												\


#==============================================================================#
#                                   Paths                                      #
#==============================================================================#

PATH_SRC := src
PATH_INC := include
PATH_OBJ := .obj
PATH_DEP := .dep

#==============================================================================#
#                                 Compilation                                  #
#==============================================================================#

LDLIBS = \

CLIBS = $(foreach dep, $(LIBS), $(dep)/$(notdir $(dep)).a) \

LTOPLUGIN="$(gcc -print-search-dirs | grep install | awk '{print $2 "liblto_plugin.so"}')"

LDFLAGS = \

CFLAGS = -I$(PATH_INC) $(FLAGS) \
		 $(foreach dep, $(LIBS), -I$(dep)/$(PATH_INC)) \
		 $(foreach dep, $(LDLIBS), -I$(dep)/$(PATH_INC)) \
		 $(foreach lib, $(SYSLIBS), -l$(lib))

#==============================================================================#
#                                   Various                                    #
#==============================================================================#

SHELL = bash

#==============================================================================#
#                             Variables Customizers                            #
#==============================================================================#

OBJS := $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))
DEPS := $(patsubst %.c, $(PATH_DEP)/%.d, $(SRCS))

#==============================================================================#
#                                    Rules                                     #
#==============================================================================#

include ../makefiles/bin.mk
include ../makefiles/strings.mk
include ../makefiles/depend.mk
include ../makefiles/test.mk
