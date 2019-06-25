/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 23:48:55 by mbeilles          #+#    #+#             */
/*   Updated: 2019/03/31 05:11:04 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool			ft_strtob(const char *str, char **end, bool *valid)
{
	(valid) ? *valid = false : false;
	if (!str)
		return (false);
	(end) ? *end = (char*)str : false;
	while (*str && ft_isspace(*str))
		str++;
	if ((*str == '0' || *str == '1') && str[1] == '\0')
		return (*str - '0');
	else if (strcasecmp(str, "yes") == 0
			|| strcasecmp(str, "true") == 0
			|| strcasecmp(str, "on") == 0)
	{
		(valid) ? *valid = true : false;
		return (true);
	}
	else if (strcasecmp(str, "off") == 0
			|| strcasecmp(str, "no") == 0
			|| strcasecmp(str, "false") == 0)
	{
		(valid) ? *valid = true : false;
		return (false);
	}
	return (false);
}
