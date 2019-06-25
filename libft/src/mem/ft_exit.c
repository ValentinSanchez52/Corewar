/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:02:45 by mbeilles          #+#    #+#             */
/*   Updated: 2019/04/25 15:20:24 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

NORETURN		ft_exit(int code, char *str,
						void (*callback)(void*))
{
	if (str)
		write(1, str, ft_strlen(str));
	if (callback)
		callback(str);
	exit(code);
}
