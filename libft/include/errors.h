/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njiall </var/spool/mail/njiall>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:39:54 by njiall            #+#    #+#             */
/*   Updated: 2019/07/01 15:39:43 by njiall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <stdbool.h>
# include "libft.h"

# define			FT_DEFAULT_DESTRUCTOR free

typedef enum		e_error_level
{
	ERR_NONE,
	ERR_INFO,
	ERR_WARN,
	ERR_CRIT,
	ERR_MAX,
	ERR_SAFE_RANGE
}					t_error_level;

typedef struct		s_error_flags
{
	bool			display_message: 1;
	bool			force_exit: 1;
}					t_error_flags;

typedef struct		s_error
{
	int				code;
	t_error_level	level;
	void			*data;
	void			(*destructor)(void *data);
	void			(*printer)(void *data, t_error_level level);
	t_error_flags	flags;
}					t_error;

void				ft_handle_error(t_error error);

#endif
