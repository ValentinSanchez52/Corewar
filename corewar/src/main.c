/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:39:16 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/04 18:25:18 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "corewar.h"
#include "bboa.h"
#include "libft.h"

// Generic help function
static t_bboa_state			help(t_arg_array *args) {
	return (BBOA_RS_DISPLAY_USAGE);
}

// Use this for debug purposes
static t_bboa_state			print_args(t_arg_array *args) {
	t_arg_token				token;
	uint32_t				i;

	i = -1;
	while (++i < args->len)
	{
		token = args->array[i];
		switch (token.type) {
			default:
				printf("Arg [NONE]: %p\n", token.none_token.data);
				break ;
			case BBOA_AT_STRING:
				printf("Arg [STRG]: %s\n", token.string_token.string);
				break ;
			case BBOA_AT_NUMBER:
				printf("Arg [NUMB]: %f\n", token.number_token.number);
				break ;
			case BBOA_AT_BOOLEAN:
				printf("Arg [BOOL]: %s\n", (token.bool_token.boolean ? "true" : "false"));
				break ;
		}
	}
	return (BBOA_RS_OK);
}

static const t_option		g_options[] = {
	(t_option){
		.option = {"help", "h"},
		.type = {OPT_DOUBLE, OPT_SINGLE},
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
		.type = {OPT_SINGLE, OPT_SINGLE},
		.length = 2,
		.match = (t_opt_match){
			.func = &print_args,
			.types = {BBOA_AT_NUMBER},
			.arg_count = 1,
			.desc = "Dump the arena state after n cycles"
		}
	},
	(t_option){
		.option = {"number", "num", "n"},
		.type = {OPT_DOUBLE, OPT_DOUBLE, OPT_SINGLE},
		.length = 3,
		.match = (t_opt_match){
			.func = &print_args,
			.types = {BBOA_AT_NUMBER, BBOA_AT_STRING},
			.arg_count = 2,
			.desc = "Sets next champion's number in args"
		}
	},
};

static inline char			**parse_options(int c, char **v, void *data)
{
	static t_opt_patterns	patterns;
	uint32_t				i;
	uint32_t				j;

	patterns = (t_opt_patterns){
			.mapd = ft_hashmap_create(),
			.maps = ft_hashmap_create(),
			.data = data
	};
	i = ~0u;
	while (++i < sizeof(g_options) / sizeof(t_option))
	{
		j = ~0u;
		while (++j < g_options[i].length)
			ft_hashmap_set((g_options[i].type[j] == OPT_SINGLE) ?
					patterns.maps : patterns.mapd,
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

	v++;
	c--;
	i = parse_options(c, v, &data) - v;
	return (0);
}
