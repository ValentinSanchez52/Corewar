/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_long_single_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:58:20 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/24 18:05:22 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashmap.h"
#include "bboa.h"
#include "libft.h"

inline t_bboa_state		parse_long_single_arg(
		char ***last,
		uint32_t arg,
		int ac,
		char **av
)
{
	t_opt_match		*match;
	t_arg_array		*tkn;
	char			*str;
	t_bboa_state	state;

	if ((str = ft_strrchr(av[0] + 1, '=')))
		*str++ = '\0';
	if ((state = ft_hashmap_get((*mtch())->maps, (uint8_t*)av[0] + 1,
					(void**)&match) && match))
	{
		if (!(tkn = generate_tokens(match, av[0] + 1, ac - arg - 1,
						(t_arg_gen){av + 1, str})))
			return (BBOA_RS_GENERIC_ERROR);
		*last = (av + tkn->len + !str > *last)
			? av + tkn->len + !str : *last;
		if ((state = match->func(tkn)) == BBOA_RS_DISPLAY_USAGE)
			bboa_set_error_usage(*mtch(), NULL, state,
					BBOA_ERR_INFO);
		ft_afree(3, tkn->array, tkn->opt, tkn);
		return (state);
	}
	if (str)
		str[-1] = '=';
	return (state ? BBOA_RS_OK : BBOA_RS_UNKNOWN_OPT);
}
