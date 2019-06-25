/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_afree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:31:46 by mbeilles          #+#    #+#             */
/*   Updated: 2019/04/22 14:33:04 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void					ft_afree(int len, ...)
{
	va_list			arg;

	va_start(arg, len);
	while (len-- > 0)
		free(va_arg(arg, void *));
	va_end(arg);
}
