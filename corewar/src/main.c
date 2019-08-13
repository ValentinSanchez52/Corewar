/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:39:16 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/13 18:00:41 by vsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "corewar.h"
#include "print.h"
#include "bboa.h"
#include "libft.h"

t_vm						g_vm = (t_vm) {
		.cycles_to_die = COR_CYCLES_DEFAULT,
		.cycles_left = COR_CYCLES_LEFT
};

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
			case BBOA_AT_DOUBLE:
				printf("\e[1;4mArg\e[0m [\e[1;34mDBLE\e[0m]: \e[34m%F\e[0m\n",
						token.double_token.number);
				break ;
			case BBOA_AT_INTEGER:
				if (token.integer_token.invalid)
					printf("\e[1;4mArg\e[0m [\e[1;34mINTG\e[0m]: \e[31mInvalid\e[0m\n");
				else
					printf("\e[1;4mArg\e[0m [\e[1;34mINTG\e[0m]: \e[34m%lld\e[0m\n",
							token.integer_token.number);
				break ;
			case BBOA_AT_BOOLEAN:
				printf("\e[1;4mArg\e[0m [\e[1;35mBOOL\e[0m]: \e[35m%s\e[0m\n",
						(token.bool_token.boolean ? "true" : "false"));
				break ;
		}
	}
	return (BBOA_RS_OK);
}

/*
** Generic help function
*/
static t_bboa_state			help(t_arg_array *args) {
	return (BBOA_RS_DISPLAY_USAGE);
}

static t_bboa_state			set_dump(t_arg_array *args) {
	print_args(args);
	if (args->len < 1 || args->array[0].type != BBOA_AT_INTEGER)
		return (BBOA_RS_NOT_ENOUGH_ARGS);
	g_vm.flags.dump_cycle = (uint32_t)args->array[0].integer_token.number;
	g_vm.flags.dump = true;
	return (BBOA_RS_OK);
}

static t_bboa_state			set_dump_size(t_arg_array *args) {
	uint32_t				arg;

	print_args(args);
	if (args->len < 1)
		return (BBOA_RS_NOT_ENOUGH_ARGS);
	if (args->array[0].type != BBOA_AT_INTEGER)
		return (BBOA_RS_TYPE_MISMATCH);
	arg = (uint32_t)args->array[0].integer_token.number;
	if (arg == 64)
		g_vm.flags.dump_size = DMP_SIZE_64;
	else if (arg == 128)
		g_vm.flags.dump_size = DMP_SIZE_128;
	else if (arg != 32)
		return (BBOA_RS_INVALID_ARG);
	return (BBOA_RS_OK);
}

static t_bboa_state			parse_player(t_arg_array *args) {
	print_args(args);
	if (args->len < 2)
		return (BBOA_RS_NOT_ENOUGH_ARGS);
	else if (args->array[0].type != BBOA_AT_INTEGER
			|| args->array[0].integer_token.invalid
			|| args->array[1].type != BBOA_AT_STRING)
		return (BBOA_RS_TYPE_MISMATCH);
	char *player = ft_strbasename(args->array[1].string_token.string);
	printf("Loading '%s' as player %u...\n", player,
			(uint32_t)args->array[0].integer_token.number);
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
			.func = &set_dump,
			.types = {BBOA_AT_INTEGER},
			.arg_count = 1,
			.desc = "Dump the arena state after [\e[37mnumber\e[0m] cycles."
		}
	},
	(t_option){
		.option = {"dump-size", "ds"},
		.type = {OPT_DOUBLE, OPT_SINGLE},
		.length = 2,
		.match = (t_opt_match){
			.func = &set_dump_size,
			.types = {BBOA_AT_INTEGER},
			.arg_count = 1,
			.desc = "Determines dump width in bytes [32|64|128]. Defaults to 32."
		}
	},
	(t_option){
		.option = {"number", "num", "n", "player", "p"},
		.type = {OPT_DOUBLE, OPT_DOUBLE, OPT_SINGLE, OPT_DOUBLE, OPT_SINGLE},
		.length = 5,
		.match = (t_opt_match){
			.func = &parse_player,
			.types = {BBOA_AT_INTEGER, BBOA_AT_STRING},
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
	int				j;
	int				data = 0;

	v++;
	c--;
	j = (parse_options(c, v, &data) - v);
	i = 0;
	printf("j: %d '%s'\n", j, v[j]);
	while (i < 4 && i + j < c)
	{
		corewar_load_warriors(i, v[j + i]);
		i++;
	}
	corewar_load_arena();
	/*print_dump(&g_vm);*/
	start_visu();
	automaton_run(&g_vm);
	/*print_dump(&g_vm);*/
	visu_end_wait();
	endwin();	//To restore terminal settings
	return (0);
}
