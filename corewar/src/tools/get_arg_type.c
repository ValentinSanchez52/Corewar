/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 06:13:53 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/26 06:25:24 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Gets the argument type at index
**
** 		arg type:1, 2, 3, 4.
** 		encode :[aa bb cc dd]
** 		              &
** 		i = 1  :[11 00 00 00] >> 1 |=> aa
** 		i = 2  :[00 11 00 00] >> 2 |=> bb
** 		i = 3  :[00 00 11 00] >> 3 |=> cc
** 		i = 4  :[00 00 00 11] >> 4 |=> dd
*/

inline t_op_arg_code	get_arg_type(
		uint8_t encode,
		uint32_t i
)
{
	return (((encode & (0b11 << (2 * (COR_ARG_NUMBER_MAX - 1 - i))))
				>> (2 * (COR_ARG_NUMBER_MAX - 1 - i))));
}
