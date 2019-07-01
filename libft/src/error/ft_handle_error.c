/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njiall </var/spool/mail/njiall>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:44:29 by njiall            #+#    #+#             */
/*   Updated: 2019/07/01 15:27:20 by njiall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "errors.h"

void						ft_handle_error(t_error error)
{
	if (error.flags.display_message && error.printer)
		error.printer(error.data, error.level);
	if (error.destructor)
		error.destructor(error.data);
	if (error.level == ERR_CRIT || error.flags.force_exit)
		exit(error.code);
}
