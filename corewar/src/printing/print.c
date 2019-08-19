/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 19:07:04 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 19:16:08 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "print.h"
#include "libft.h"

void				printer(t_print print)
{
	static const char * const	headers[LOG_MAX] = {
		[LOG_DEBUG] = "\e[0;37m[\e[1;34m?\e[0;37m]\e[0m ",
		[LOG_INFO] = "\e[0;37m[\e[1;34mi\e[0;37m]\e[0m ",
		[LOG_WARN] = "\e[0;37m[\e[1;33m!\e[0;37m]\e[0m ",
		[LOG_CRIT] = "\e[0;37m[\e[1;31mx\e[0;37m]\e[0m ",
	};
	char			*msg;

	if (print.flags.silent)
		return ;
	if (!print.flags.no_header)
	{
		msg = ft_strajoin(2, headers[print.level], print.data);
		write(1, msg, ft_strlen(msg));
		free(msg);
	}
	else
		write(1, print.data, ft_strlen(print.data));
}

void				print(t_print print)
{
	if (print.printer && !print.flags.silent
			&& !(!print.flags.debug && print.level == LOG_DEBUG))
		print.printer(print);
	if (print.data && print.destructor)
		print.destructor(print.data);
	if (print.level == LOG_CRIT || print.flags.exit
			|| (print.flags.strict && print.level == LOG_WARN))
		exit(print.code);
}
