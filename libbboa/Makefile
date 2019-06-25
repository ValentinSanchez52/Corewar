# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/04 04:17:21 by mbeilles          #+#    #+#              #
#    Updated: 2019/05/25 10:16:05 by mbeilles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#
#                                   Naming                                     #
#==============================================================================#

NAME = libbboa.a

NICK = ARG
PROJECT_COLOR = "\033[38;5;250m"
PROJECT_COLOR_ALT = "\033[38;5;248m"

CC = gcc

#==============================================================================#
#                                   Sources                                    #
#==============================================================================#

SRCS = $(PATH_SRC)/parse_args.c						\
	   $(PATH_SRC)/parse_functions.c				\
	   $(PATH_SRC)/print_functions.c				\
	   $(PATH_SRC)/get_usage.c						\
	   $(PATH_SRC)/get_usage_error.c				\

INCS = $(PATH_INC)/bboa.h							\

LIBS = \

NODEP_LIBS = ../libft \

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

LDLIBS = $(foreach dep, $(NODEP_LIBS), $(dep)/$(notdir $(dep)).a) \

LDFLAGS = \

CLIBS = $(foreach dep, $(LIBS), $(dep)/$(notdir $(dep)).a) \

CFLAGS = -I$(PATH_INC) $(FLAGS) \
		 $(foreach dep, $(LIBS), -I$(dep)/$(PATH_INC)) $(FLAGS) \
		 $(foreach dep, $(NODEP_LIBS), -I$(dep)/$(PATH_INC)) $(FLAGS) \

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

$(NAME): $(CLIBS) $(OBJS)
	@printf $(START_MSG)
	@printf $(MAKING_PROGRESS)
	@ar -rc $@ $(OBJS); \
		if [ "$$?" != "1" ]; then \
			printf $(MAKING_SUCCESS); \
			exit 0; \
		else \
			printf $(MAKING_FAILURE); \
			exit 2; \
		fi
	@ranlib $(NAME)
	@chmod +x $(NAME)

all: $(NAME)

clean:
	@-rm -rf $(PATH_OBJ)
	@printf $(CLEANING_OBJS)

fclean: clean
	@-rm -f $(NAME)
	@printf $(CLEANING_BINS)

re: fclean all

FORCE:

.PHONY: debug depend all fclean clean re FORCE

include ../makefiles/strings.mk
include ../makefiles/depend.mk
