/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 07:13:45 by mbeilles          #+#    #+#             */
/*   Updated: 2019/05/21 07:22:38 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include "dynarray.h"
#include "libft.h"

char			*ft_get_fd_content(int fd)
{
	t_dynarray	*str;
	char		*s;
	static char	buffer[BUFF_SIZE];
	ssize_t		n;

	if (!(str = ft_dynarray_create(0, 0)))
		return (NULL);
	while ((n = read(fd, buffer, BUFF_SIZE)) > 0)
		ft_dynarray_push(str, buffer, n);
	ft_dynarray_push(str, "", 1);
	s = (char*)str->array;
	free(str);
	return (s);
}
