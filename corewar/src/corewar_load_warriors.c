/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_load_warriors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:28:42 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/24 19:19:29 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include "corewar.h"
#include "libft.h"
#include "dynarray.h"

static const char	*g_messages[0xff] = {
	[0b01111111] = "Error reading magic in <path>.\n",
	[0b01111110] = "Error reading name in <path>.\n",
	[0b01111100] = "Error reading padding in <path>.\n",
	[0b01111000] = "Error reading code size in <path>.\n",
	[0b01110000] = "Error reading comment in <path>.\n",
	[0b01100000] = "Error reading padding in <path>.\n",
	[0b01000000] = "Error reading code in <path>.\n",
	[0b10000000] = "Error opening <path>.\n",
	[0b10001000] = "Size of warrior is too big in <path>.\n"
};

static inline char	*get_error_message(uint8_t code, char *wname)
{
	if (g_messages[code])
		return (ft_strreplace(g_messages[code], "<path>", wname));
	return (NULL);
}

static inline
uint32_t			macos_flip_bytes(uint32_t n)
{
	uint32_t		returned_bytes;

	((uint8_t*)&returned_bytes)[0] = ((uint8_t*)&n)[3];
	((uint8_t*)&returned_bytes)[1] = ((uint8_t*)&n)[2];
	((uint8_t*)&returned_bytes)[2] = ((uint8_t*)&n)[1];
	((uint8_t*)&returned_bytes)[3] = ((uint8_t*)&n)[0];
	return (returned_bytes);
}

static inline
uint8_t				get_warrior(char *file, t_warrior *warrior)
{
	int				fd;
	uint8_t			err_code;
	char			padding[WARRIOR_PADDING];
	int				ret;

	if ((fd = open(file, O_RDONLY)) <= 0)
		return (0b10000000);
	err_code = ((read(fd, &(warrior->magic), WARRIOR_MAGIC)) <= 0) << 0;
	warrior->magic = macos_flip_bytes(warrior->magic);
	ret = read(fd, &(warrior->name), WARRIOR_NAME);
	warrior->name[ret] = 0;
	err_code |= (ret <= 0) << 1;
	err_code |= (read(fd, &padding, WARRIOR_PADDING) <= 0) << 2;
	err_code |= ((read(fd, &(warrior->assembly_size), WARRIOR_SIZE)) <= 0) << 3;
	warrior->assembly_size = macos_flip_bytes(warrior->assembly_size);
	if (!(warrior->assembly_size <= WARRIOR_MAX_SIZE))
		return (0b10001000);
	ret = read(fd, &(warrior->comment), WARRIOR_COMMENT);
	warrior->comment[ret] = 0;
	err_code |= (ret <= 0) << 4;
	err_code |= (read(fd, &padding, WARRIOR_PADDING) <= 0) << 2;
	err_code |= (read(fd, &(warrior->assembly), warrior->assembly_size) <= 0) << 5;
	return (err_code);
}

void				corewar_load_warriors(int c, char *file)
{
	uint8_t			err_code;

	if ((err_code = get_warrior(file, &(vm.warriors[c]))))
		printf("%s", get_error_message(err_code, file));
	else
	{
		vm.warriors[c].id = UINT32_MAX - c;
		vm.warriors_nb++;
	}
}
