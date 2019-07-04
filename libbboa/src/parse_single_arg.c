/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:02:21 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/04 19:38:35 by mbeilles         ###   ########.fr       */
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
**	| Parse all single dash options contained in the argument string |
**	For norm purposes the return state is stored at the end of `s`.
**		`str` points to the start of what is after '='.
**
**	This function loops over each char of the arguement until a '=' or the end.
**		for each char it copies to `s` so that it's a string only containing it.
**		then it generate tokens as above.
**	If the state of return is different of OK it asumes there's an error
**		and prints.
**	Then frees the token and it's content.
*/

t_bboa_state		parse_single_arg(
		char ***lt,
		uint32_t arg,
		int ac,
		char **av
)
{
	t_opt_match		*mth;
	t_arg_array		*tkn;
	static char		s[3] = " \0";
	char			*str;
	uint32_t		i;

	s[2] = (char)BBOA_RS_OK;
	i = 0;
	if ((str = ft_strrchr(av[0] + 2, '=')))
		*str++ = '\0';
	while (s[2] <= BBOA_RS_OK && (s[0] = av[0][++i]))
		if (ft_hashmap_get((*mtch())->maps, (uint8_t*)s, (void**)&mth) && mth)
		{
			if (!(tkn = generate_tokens(mth, s, ac - (*lt - av) + !!str,
							(t_arg_gen){.args = *lt, .first = (av[0]
									+ i + 2 == str) ? str : NULL})))
				return (BBOA_RS_GENERIC_ERROR);
			*lt += tkn->len - (av[0] + i + 2 == str);
			if ((s[2] = mth->func(tkn)) == BBOA_RS_DISPLAY_USAGE)
				bboa_set_error_usage(*mtch(), NULL, s[2], BBOA_ERR_INFO);
			ft_afree(3, tkn->array, tkn->opt, tkn);
		}
		else
			return (bboa_set_error_usage(*mtch(), s, BBOA_NOT, BBOA_EC));
	return ((t_bboa_state)s[2]);
}
