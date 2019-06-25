# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/18 08:44:32 by mbeilles          #+#    #+#              #
#    Updated: 2019/06/14 11:02:39 by mbeilles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#
#                                   Naming                                     #
#==============================================================================#

NAME = libft.a

NICK = LFT
PROJECT_COLOR = "\033[38;5;214m"
PROJECT_COLOR_ALT = "\033[38;5;172m"

CC = gcc

#==============================================================================#
#                                   Sources                                    #
#==============================================================================#

SRCS = \
	   $(PATH_SRC)/error/ft_error.c											\
	   $(PATH_SRC)/error/ft_error_exit.c									\
	   $(PATH_SRC)/types/ft_get_pow.c										\
	   $(PATH_SRC)/types/ft_isspace.c										\
	   $(PATH_SRC)/types/ft_isalnum.c										\
	   $(PATH_SRC)/types/ft_isalpha.c										\
	   $(PATH_SRC)/types/ft_isdigit.c										\
	   $(PATH_SRC)/types/ft_isascii.c										\
	   $(PATH_SRC)/types/ft_isprint.c										\
	   $(PATH_SRC)/types/ft_isset.c											\
	   $(PATH_SRC)/list/ft_lstadd.c											\
	   $(PATH_SRC)/list/ft_lstdel.c											\
	   $(PATH_SRC)/list/ft_lstdelone.c										\
	   $(PATH_SRC)/list/ft_lstinvert_iter.c									\
	   $(PATH_SRC)/list/ft_lstiter.c										\
	   $(PATH_SRC)/list/ft_lstmap.c											\
	   $(PATH_SRC)/list/ft_lstnew.c											\
	   $(PATH_SRC)/mem/ft_afree.c											\
	   $(PATH_SRC)/mem/ft_bzero.c											\
	   $(PATH_SRC)/mem/ft_exit.c											\
	   $(PATH_SRC)/mem/ft_mem_block.c										\
	   $(PATH_SRC)/mem/ft_mem_block_extension.c								\
	   $(PATH_SRC)/mem/ft_memalloc.c										\
	   $(PATH_SRC)/mem/ft_memdup.c											\
	   $(PATH_SRC)/mem/ft_memcpy.c											\
	   $(PATH_SRC)/mem/ft_memccpy.c											\
	   $(PATH_SRC)/mem/ft_memchr.c											\
	   $(PATH_SRC)/mem/ft_memcmp.c											\
	   $(PATH_SRC)/mem/ft_memdel.c											\
	   $(PATH_SRC)/mem/ft_memmove.c											\
	   $(PATH_SRC)/mem/ft_memset.c											\
	   $(PATH_SRC)/mem/ft_realloc.c											\
	   $(PATH_SRC)/str/ft_atoi.c											\
	   $(PATH_SRC)/str/ft_get_file_content.c								\
	   $(PATH_SRC)/str/ft_get_fd_content.c									\
	   $(PATH_SRC)/str/ft_get_next_line.c									\
	   $(PATH_SRC)/str/ft_itoa.c											\
	   $(PATH_SRC)/str/ft_putstr.c											\
	   $(PATH_SRC)/str/ft_putstr_fd.c										\
	   $(PATH_SRC)/str/ft_putchar.c											\
	   $(PATH_SRC)/str/ft_putchar_fd.c										\
	   $(PATH_SRC)/str/ft_putendl.c											\
	   $(PATH_SRC)/str/ft_putendl_fd.c										\
	   $(PATH_SRC)/str/ft_putnbr.c											\
	   $(PATH_SRC)/str/ft_putnbr_fd.c										\
	   $(PATH_SRC)/str/ft_strncpy.c											\
	   $(PATH_SRC)/str/ft_strcat.c											\
	   $(PATH_SRC)/str/ft_strcdup.c											\
	   $(PATH_SRC)/str/ft_strreplace.c										\
	   $(PATH_SRC)/str/ft_strchr.c											\
	   $(PATH_SRC)/str/ft_strrchr.c											\
	   $(PATH_SRC)/str/ft_strclr.c											\
	   $(PATH_SRC)/str/ft_strlen.c											\
	   $(PATH_SRC)/str/ft_strcmp.c											\
	   $(PATH_SRC)/str/ft_strcpy.c											\
	   $(PATH_SRC)/str/ft_strdel.c											\
	   $(PATH_SRC)/str/ft_strdup.c											\
	   $(PATH_SRC)/str/ft_strequ.c											\
	   $(PATH_SRC)/str/ft_striter.c											\
	   $(PATH_SRC)/str/ft_striteri.c										\
	   $(PATH_SRC)/str/ft_strjoin.c											\
	   $(PATH_SRC)/str/ft_strajoin.c										\
	   $(PATH_SRC)/str/ft_strlcat.c											\
	   $(PATH_SRC)/str/ft_strmap.c											\
	   $(PATH_SRC)/str/ft_strmapi.c											\
	   $(PATH_SRC)/str/ft_strncat.c											\
	   $(PATH_SRC)/str/ft_strncmp.c											\
	   $(PATH_SRC)/str/ft_strndup.c											\
	   $(PATH_SRC)/str/ft_strnequ.c											\
	   $(PATH_SRC)/str/ft_strnew.c											\
	   $(PATH_SRC)/str/ft_strnstr.c											\
	   $(PATH_SRC)/str/ft_strsplit.c										\
	   $(PATH_SRC)/str/ft_strstr.c											\
	   $(PATH_SRC)/str/ft_strskip.c											\
	   $(PATH_SRC)/str/ft_strsub.c											\
	   $(PATH_SRC)/str/ft_strtod.c											\
	   $(PATH_SRC)/str/ft_strtol.c											\
	   $(PATH_SRC)/str/ft_strtob.c											\
	   $(PATH_SRC)/str/ft_strtrim.c											\
	   $(PATH_SRC)/str/ft_tolower.c											\
	   $(PATH_SRC)/str/ft_toupper.c											\
	   $(PATH_SRC)/str/ft_t_string_new.c									\
	   $(PATH_SRC)/str/ft_t_string_concat.c									\
	   $(PATH_SRC)/str/ft_t_string_concat_len.c								\
	   $(PATH_SRC)/str/ft_t_string_expand.c									\
	   $(PATH_SRC)/str/ft_ltostr.c											\
	   $(PATH_SRC)/str/ft_ultostr.c											\
	   $(PATH_SRC)/dynarray/ft_dynarray_create.c							\
	   $(PATH_SRC)/dynarray/ft_dynarray_manipulate.c						\
	   $(PATH_SRC)/dynarray/ft_dynarray_iterate.c							\
	   $(PATH_SRC)/dynarray/ft_dynarray_remove.c							\
	   $(PATH_SRC)/dynarray/ft_dynarray_resize.c							\
	   $(PATH_SRC)/dynarray/ft_dynarray_store.c								\
	   $(PATH_SRC)/dynarray/ft_dynarray_push_str.c							\
	   $(PATH_SRC)/hashmap/ft_hashmap_create.c								\
	   $(PATH_SRC)/hashmap/ft_hashmap_hash.c								\
	   $(PATH_SRC)/hashmap/ft_hashmap_manipulation.c						\

INCS = $(PATH_INC)/libft.h													\
	   $(PATH_INC)/get_next_line.h											\
	   $(PATH_INC)/hashmap.h												\
	   $(PATH_INC)/dynarray.h												\

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

CLIBS = $(foreach dep, $(LIBS), $(dep)/$(dep).a) \

LDFLAGS = \

CFLAGS = -I$(PATH_INC) $(FLAGS) \
		 $(foreach dep, $(LIBS), -I$(dep)/$(PATH_INC)) $(FLAGS) \

FAST_FLAG = -O3 -march=native -flto
SLOW_FLAG = -fsanitize=address -g3 -O0

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
