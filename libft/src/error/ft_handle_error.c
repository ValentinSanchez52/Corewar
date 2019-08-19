/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 21:18:49 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 21:18:51 by mbeilles         ###   ########.fr       */
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
