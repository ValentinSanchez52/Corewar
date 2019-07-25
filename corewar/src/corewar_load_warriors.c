/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_load_warriors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:28:42 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/25 18:30:42 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "corewar.h"
#include "libft.h"
#include "dynarray.h"

static const char					*g_messages[0xff] = {
	[0b00000001] = "Wrong magic number in <path>.\n",
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

static inline char					*get_error_message(uint8_t code,
		char *wname)
{
	if (g_messages[code])
		return (ft_strreplace(g_messages[code], "<path>", wname));
	return (NULL);
}

static inline bool					check_magic_validity(t_warrior *warrior)
{
	warrior->magic = macos_flip_bytes(warrior->magic);
	return (warrior->magic == WARRIOR_DEFAULT_MAGIC);
}

static inline uint8_t				get_warrior(char *file, t_warrior *wrrr)
{
	int				fd;
	uint8_t			err_code;
	char			padding[WARRIOR_PADDING];
	int				ret;

	if ((fd = open(file, O_RDONLY)) <= 0)
		return (0b10000000);
	err_code = ((read(fd, &(wrrr->magic), WARRIOR_MAGIC)) <= 0) << 0;
	if (!check_magic_validity(wrrr))
		return (0b00000001);
	ret = read(fd, &(wrrr->name), WARRIOR_NAME);
	wrrr->name[ret] = 0;
	err_code |= (ret <= 0) << 1;
	err_code |= (read(fd, &padding, WARRIOR_PADDING) <= 0) << 2;
	err_code |= ((read(fd, &(wrrr->assembly_size), WARRIOR_SIZE)) <= 0) << 3;
	wrrr->assembly_size = macos_flip_bytes(wrrr->assembly_size);
	if (!(wrrr->assembly_size <= WARRIOR_MAX_SIZE))
		return (0b10001000);
	ret = read(fd, &(wrrr->comment), WARRIOR_COMMENT);
	wrrr->comment[ret] = 0;
	err_code |= (ret <= 0) << 4;
	err_code |= (read(fd, &padding, WARRIOR_PADDING) <= 0) << 2;
	err_code |= (read(fd, &(wrrr->assembly), wrrr->assembly_size) <= 0) << 5;
	close(fd);
	return (err_code);
}

void								corewar_load_warriors(int c, char *file)
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
