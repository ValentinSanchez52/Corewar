/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_end_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:01:07 by vsanchez          #+#    #+#             */
/*   Updated: 2019/08/16 08:03:10 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
/*
**	endwin();	//To restore terminal settings
*/

inline void				visu_end_wait(void)
{
	uint32_t		key;

	while ((key = getch()) == ERR)
		continue ;
	endwin();
}
