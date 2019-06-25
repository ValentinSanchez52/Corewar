/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:44:42 by mbeilles          #+#    #+#             */
/*   Updated: 2019/04/24 18:01:15 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

static void		ft_get_file_content_string(t_string *string, int fd)
{
	static char	buffer[BUFF_SIZE];
	ssize_t		n;

	while ((n = read(fd, buffer, BUFF_SIZE)) > 0)
		ft_t_string_concat_len(string, buffer, (uint32_t)n);
}

char			*ft_get_file_content(char *filename)
{
	t_string	string;
	int			fd;

	if (!(string.string = (char*)malloc(sizeof(char) * 256)))
		return (NULL);
	string.capacity = 256;
	string.len = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	string.string[0] = '\0';
	ft_get_file_content_string(&string, fd);
	return (string.string);
}
