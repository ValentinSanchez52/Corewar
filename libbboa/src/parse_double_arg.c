/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:02:47 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/04 19:01:57 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashmap.h"
#include "bboa.h"
#include "libft.h"

/*
**	| Parse a double dash option and it's arguments |
**		`str` points to the start of what is after '='.
**
**	This function gets of there's is a match for the argument
**		then generate tokens.
**	If the state of return is different of OK it asumes there's an error
**		and prints.
**	Then frees the token and it's content.
*/

t_bboa_state		parse_double_arg(
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

	if ((str = ft_strrchr(av[0] + 2, '=')))
		*str++ = '\0';
	if (ft_hashmap_get((*mtch())->mapd, (uint8_t*)av[0] + 2,
				(void**)&match) && match)
	{
		if (!(tkn = generate_tokens(match, av[0] + 2, ac - arg - 1,
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
	else
		return (bboa_set_error_usage(*mtch(), av[0] + 2, BBOA_NOT, BBOA_EC));
	return (BBOA_RS_OK);
}
