/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_default_error_printer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njiall </var/spool/mail/njiall>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:27:49 by njiall            #+#    #+#             */
/*   Updated: 2019/07/01 15:41:39 by njiall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include "libft.h"
#include "errors.h"

static const char * const	g_headers[ERR_MAX] = {
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
