/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 19:00:17 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 19:12:53 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <stdbool.h>

typedef enum			e_print_level
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_CRIT,
	LOG_MAX,
	LOG_SAFE_RANGE
}						t_print_level;

typedef enum			e_print_code
{
	ERR_ALLOC,
	ERR_NO_SPACE,
	ERR_GENERIC,
	ERR_MAX,
	ERR_SAFE_RANGE
}						t_print_code;

typedef enum			e_dump_size
{
	DMP_SIZE_32,
	DMP_SIZE_64,
	DMP_SIZE_128,
	DMP_SIZE_MAX
}						t_dump_size;

typedef struct			s_print_flags
{
	bool				exit : 1;
	bool				silent : 1;
	bool				strict : 1;
	bool				no_header : 1;
	bool				debug : 1;
}						t_print_flags;

typedef struct			s_print
{
	t_print_code		code;
	t_print_level		level;
	t_print_flags		flags;
	void				*data;
	void				(*printer)(struct s_print);
	void				(*destructor)(void *);
}						t_print;

void					print_vm(t_print print);
void					print(t_print print);
void					printer(t_print print);
# define PRINT_DESTROY	(&free)

#endif
