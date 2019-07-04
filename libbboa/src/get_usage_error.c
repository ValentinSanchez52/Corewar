/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_usage_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:14:47 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/04 19:00:31 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "bboa.h"

void				bboa_usage_error_destructor(t_bboa_error error)
{
	free(error.message);
}

t_bboa_state		bboa_set_error_usage(
		t_opt_patterns *options,
		char *match,
		t_bboa_state state,
		t_bboa_error_level level
)
{
	g_bboa_error = (t_bboa_error){
		.level = level,
		.state = state,
		.match = match,
		.argument = NULL,
		.message = bboa_get_usage(options),
		.destructor = &bboa_usage_error_destructor
	};
	return (state);
}
