/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:39:16 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/01 15:44:48 by njiall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "corewar.h"
#include "bboa.h"
#include "libft.h"

static t_bboa_state			help(t_arg_array *args) {
	return (BBOA_RS_DISPLAY_USAGE);
}

static const t_option		g_options[] = {
	(t_option){
		.option = {"help", "h"},
		.length = 2,
		.match = (t_opt_match){
			.func = &help,
			.types = {},
			.arg_count = 0,
			.desc = "Show this usage"
		}
	},
	(t_option){
		.option = {"dump", "d"},
		.length = 2,
		.match = (t_opt_match){
			.func = &help,
			.types = {BBOA_AT_NUMBER},
			.arg_count = 1,
			.desc = "Dump the arena state after n cycles"
		}
	},
	(t_option){
		.option = {"number", "n"},
		.length = 2,
		.match = (t_opt_match){
			.func = &help,
			.types = {BBOA_AT_NUMBER, BBOA_AT_STRING},
			.arg_count = 2,
			.desc = "Sets next champion's number in args"
		}
	},
};

static inline char			**parse_options(int c, char **v, void *data)
{
	static t_opt_patterns	patterns;
	t_option				*options;
	uint32_t				i;
	uint32_t				j;

	patterns = (t_opt_patterns){.map = ft_hashmap_create(), .data = data};
	i = ~0u;
	while (++i < sizeof(g_options) / sizeof(t_option))
	{
		j = ~0u;
		while (++j < g_options[i].length)
			ft_hashmap_set(patterns.map,
					(uint8_t*)g_options[i].option[j],
					(t_opt_match*)&g_options[i].match);
	}
	return (bboa_parse_args(&patterns, c, v));
}

int					main(int c, char **v)
{
	char			*file;
	int				i;
	int				data;

	i = 0;
	if (v++ && (--c || 1) && (i = parse_options(c - i, v + i, &data) - v) >= c)
		if (!(file = ft_get_fd_content(0)))
			return (1);
		else
			printf("wow");
	else if (!(file = ft_get_file_content(v[i])))
		return (1);
	else
		printf("wow");
	return (0);
}
