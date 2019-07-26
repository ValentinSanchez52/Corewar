/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:39:16 by mbeilles          #+#    #+#             */
/*   Updated: 2019/07/26 08:02:44 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "corewar.h"
#include "bboa.h"
#include "libft.h"

t_vm						vm = (t_vm) {
		.cycles_to_die = COR_CYCLES_DEFAULT,
		.cycles_left = COR_CYCLES_LEFT
};

/*
** Generic help function
*/
static t_bboa_state			help(t_arg_array *args) {
	return (BBOA_RS_DISPLAY_USAGE);
}

/*
** Use this for debug purposes
*/
static t_bboa_state			print_args(t_arg_array *args) {
	t_arg_token				token;
	uint32_t				i;

	i = -1;
	printf("Printing for option \e[1;32m'\e[1;36m%s\e[32m'\e[0m \
\e[1;36m-\e[0;36m>\e[0m data: \e[36m%p\e[0m\n", args->opt, args->data);
	while (++i < args->len)
	{
		token = args->array[i];
		switch (token.type) {
			default:
				printf("\e[1;4mArg\e[0m [\e[1;33mNONE\e[0m]: \e[33m%p\e[0m\n",
						token.none_token.data);
				break ;
			case BBOA_AT_STRING:
				printf("\e[1;4mArg\e[0m [\e[1;32mSTRG\e[0m]: \e[32m%s\e[0m\n",
						token.string_token.string);
				break ;
			case BBOA_AT_NUMBER:
				printf("\e[1;4mArg\e[0m [\e[1;34mNMBR\e[0m]: \e[4;34m%d\e[0m-[\e[34m%f\e[0m]\n",
						(int)token.number_token.number, token.number_token.number);
				break ;
			case BBOA_AT_BOOLEAN:
				printf("\e[1;4mArg\e[0m [\e[1;35mBOOL\e[0m]: \e[35m%s\e[0m\n",
						(token.bool_token.boolean ? "true" : "false"));
				break ;
		}
	}
	return (BBOA_RS_OK);
}

static t_bboa_state			parse_player(t_arg_array *args) {
	print_args(args);
	if (args->len < 2)
		return (BBOA_RS_NOT_ENOUGH_ARGS);
	else if (args->array[0].type != BBOA_AT_NUMBER
			|| args->array[1].type != BBOA_AT_STRING)
		return (BBOA_RS_TYPE_MISMATCH);
	char *player = ft_strbasename(args->array[1].string_token.string);
	printf("Loading '%s' as player %u...\n", player,
			(uint32_t)args->array[0].number_token.number);
	free(player);
	return (BBOA_RS_OK);
}

static const t_option		g_options[] = {
	(t_option){
		.option = {"help", "h"},
		.type = {OPT_DOUBLE, OPT_SINGLE},
		.length = 2,
		.match = (t_opt_match){
			.func = &help,
			/*.types = {},*/
			.arg_count = 0,
			.desc = "Show this usage."
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
			.desc = "Dump the arena state after [\e[37mnumber\e[0m] cycles."
		}
	},
	(t_option){
		.option = {"number", "num", "n", "player", "p"},
		.type = {OPT_DOUBLE, OPT_DOUBLE, OPT_SINGLE, OPT_DOUBLE, OPT_SINGLE},
		.length = 5,
		.match = (t_opt_match){
			.func = &parse_player,
			.types = {BBOA_AT_NUMBER, BBOA_AT_STRING},
			.arg_count = 2,
			.desc = "Sets champion's(\e[37margument\e[0m) [\e[37mnumber\e[0m]."
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
	if (c == 0)
	{
		bboa_set_error_usage(&patterns, NULL, BBOA_RS_DISPLAY_USAGE, BBOA_ERR_NO);
		bboa_print_error(g_bboa_error);
	}
	return (bboa_parse_args(&patterns, c, v));
}

int					main(int c, char **v)
{
	int				i;
	int				data = 0;

	v++;
	c--;
	i = parse_options(c, v, &data) - v;
	/*examples :*/
	/*corewar_load_warriors(1, "champs/examples/bigzork.cor");*/
	/*corewar_load_warriors(3, "champs/examples/bigzork.cor");*/
	corewar_load_arena();
	automaton_run(&vm);
	print_dump(&vm);
	return (0);
}
