/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 19:00:17 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/25 16:09:26 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <stdbool.h>

typedef enum			e_print_level
{
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

typedef struct			s_print_flags
{
	bool				exit;
	bool				silent;
	bool				strict;
	bool				no_header;
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

void					print(t_print print);
void					printer(t_print print);
# define PRINT_DESTROY	(&free)

#endif
