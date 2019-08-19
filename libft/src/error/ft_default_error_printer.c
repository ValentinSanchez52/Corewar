/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_error_printer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:17:49 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 21:18:36 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include "libft.h"
#include "errors.h"

static const char *const	g_headers[ERR_MAX] = {
	[ERR_NONE] = "[?]",
	[ERR_INFO] = "[i]",
	[ERR_WARN] = "[!]",
	[ERR_CRIT] = "[x]",
};

void				ft_default_error_printer(
		void *data,
		t_error_level level
)
{
	const char		*hd;
	char			*msg;

	if (level >= ERR_NONE && level < ERR_MAX)
		hd = g_headers[level];
	else
		hd = NULL;
	msg = ft_strajoin(2, hd, data);
	write(2, msg, ft_strlen(msg));
	free(msg);
}
