/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:03:56 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/24 18:15:24 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdint.h>
# include <stdbool.h>
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

#endif
