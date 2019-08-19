/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bboa.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 04:11:57 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 20:43:42 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BBOA_H
# define BBOA_H

# include <stdint.h>
# include <stdbool.h>
# include "hashmap.h"

/*
** =============================================================================
*/

typedef enum			e_bboa_state
{
	BBOA_RS_NONE = 0,
	BBOA_RS_OK,
	BBOA_RS_DISPLAY_USAGE,
	BBOA_RS_UNKNOWN_OPT,
	BBOA_RS_NO_ARG,
	BBOA_RS_NOT_ENOUGH_ARGS,
	BBOA_RS_GENERIC_ERROR,
	BBOA_RS_TYPE_MISMATCH,
	BBOA_RS_MULTIPLE_REFS,
	BBOA_RS_INVALID_ARG,
	BBOA_RS_MAX_STATE
}						t_bboa_state;

# define BBOA_DU  BBOA_RS_DISPLAY_USAGE
# define BBOA_NOT BBOA_RS_UNKNOWN_OPT
# define BBOA_NA  BBOA_RS_NO_ARG
# define BBOA_NEA BBOA_RS_NOT_ENOUGH_ARGS
# define BBOA_GE  BBOA_RS_GENERIC_ERROR
# define BBOA_TM  BBOA_RS_TYPE_MISMATCH
# define BBOA_MR  BBOA_RS_MULTIPLE_REFS

# define BBOA_EC  BBOA_ERR_CRIT
# define BBOA_IF  BBOA_ERR_INFO

typedef enum			e_bboa_error_level
{
	BBOA_ERR_NO,
	BBOA_ERR_INFO,
	BBOA_ERR_WARN,
	BBOA_ERR_CRIT,
	BBOA_ERR_MAX_LEVEL
}						t_bboa_error_level;

typedef struct			s_bboa_parse_args
{
	uint32_t			arg;
	t_bboa_state		st;
	char				**last_args;
}						t_bboa_parse_args;

typedef struct			s_bboa_error
{
	t_bboa_state		state;
	t_bboa_error_level	level;
	char				*message;
	char				*match;
	char				*argument;
	void				(*destructor)(struct s_bboa_error);
}						t_bboa_error;

typedef enum			e_arg_type
{
	BBOA_AT_NONE = 0,
	BBOA_AT_STRING,
	BBOA_AT_DOUBLE,
	BBOA_AT_INTEGER,
	BBOA_AT_BOOLEAN,
	BBOA_AT_MAX_TYPE
}						t_arg_type;

typedef struct			s_usage_str
{
	char				*first;
	uint32_t			len;
	bool				type;
	char				*desc;
}						t_usage_str;

/*
** =============================================================================
** 							ARGHS
** =============================================================================
*/

typedef struct			s_arg_token_string
{
	t_arg_type			type;
	void				*data;
	char				*string;
	uint64_t			len;
}						t_arg_token_string;

typedef struct			s_arg_token_double
{
	t_arg_type			type;
	void				*data;
	double				number;
}						t_arg_token_double;

typedef struct			s_arg_token_integer
{
	t_arg_type			type;
	void				*data;
	long long			number;
	bool				invalid;
}						t_arg_token_integer;

typedef struct			s_arg_token_bool
{
	t_arg_type			type;
	void				*data;
	bool				boolean;
}						t_arg_token_bool;

typedef struct			s_arg_token_none
{
	t_arg_type			type;
	void				*data;
}						t_arg_token_none;

/*
** =============================================================================
** 							TOKENS
** =============================================================================
*/

typedef union			u_arg_token
{
	t_arg_type			type;
	t_arg_token_string	string_token;
	t_arg_token_double	double_token;
	t_arg_token_integer	integer_token;
	t_arg_token_bool	bool_token;
	t_arg_token_none	none_token;
}						t_arg_token;

typedef struct			s_arg_array
{
	char				*opt;
	uint32_t			opt_len;
	uint32_t			len;
	t_arg_token			*array;
	void				*data;
}						t_arg_array;

typedef struct			s_arg_gen
{
	char				**args;
	char				*first;
}						t_arg_gen;

typedef t_bboa_state	(*t_opt_function)(t_arg_array*);
typedef t_arg_token		(*t_convert_function)(char*);

typedef struct			s_opt_match {
	uint8_t				arg_count;
	t_opt_function		func;
	const t_arg_type	types[256];
	char				*desc;
}						t_opt_match;

typedef struct			s_opt_patterns
{
	t_hashmap			*maps;
	t_hashmap			*mapd;
	void				*data;
}						t_opt_patterns;

/*
** =============================================================================
** 							FUNCTIONS
** =============================================================================
*/

/*
**	This the only function you are supposed to use in this library.
**		For explaination on the inner workings of the function check the source.
**	- pattern options: A hash map containing t_opt_match matched by the string
**		of the corresponding options.
**	- argc: The number of strings contained in argv.
**	- argv: An array of strings on which you want to check options.
*/

t_opt_patterns			**mtch(void);

char					**bboa_parse_args(
		t_opt_patterns *opt,
		int ac,
		char **av
);

t_bboa_state			parse_long_single_arg(
		char ***last_arg,
		uint32_t args_left,
		int ac,
		char **av
);
t_bboa_state			parse_single_arg(
		char ***last_arg,
		uint32_t args_left,
		int ac,
		char **av
);
t_bboa_state			parse_double_arg(
		char ***last_arg,
		uint32_t args_left,
		int ac,
		char **av
);
t_arg_array				*generate_tokens(
		t_opt_match *match,
		char *opt,
		uint32_t args_left,
		t_arg_gen gen
);

t_bboa_error			*bboa_get_error(void);
void					bboa_print_error(t_bboa_error error);
char					*bboa_get_usage(t_opt_patterns *opts);
void					bboa_usage_error_destructor(t_bboa_error error);
t_bboa_state			bboa_set_error_usage(t_opt_patterns *opts, char *match,
								t_bboa_state state, t_bboa_error_level level);

bool					bboa_is_double(char *av);
bool					bboa_is_single(char *av);

/*
**	This is there for internal functioning of the lib.
*/

t_arg_token				bboa_parse_double(char *v);
t_arg_token				bboa_parse_integer(char *v);
t_arg_token				bboa_parse_boolean(char *v);
t_arg_token				bboa_parse_void(char *v);
t_arg_token				bboa_parse_string(char *v);

int						bboa_compare_usage_str(const void *e1, const void *e2);

extern t_bboa_error		g_bboa_error;

#endif
