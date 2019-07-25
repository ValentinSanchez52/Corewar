/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flip_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanchez <vsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:59:23 by vsanchez          #+#    #+#             */
/*   Updated: 2019/07/25 16:17:47 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

inline uint32_t			macos_flip_bytes(uint32_t n)
{
	uint32_t		returned_bytes;

	((uint8_t*)&returned_bytes)[0] = ((uint8_t*)&n)[3];
	((uint8_t*)&returned_bytes)[1] = ((uint8_t*)&n)[2];
	((uint8_t*)&returned_bytes)[2] = ((uint8_t*)&n)[1];
	((uint8_t*)&returned_bytes)[3] = ((uint8_t*)&n)[0];
	return (returned_bytes);
}
