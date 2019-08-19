/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 14:39:16 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 19:33:07 by mbeilles         ###   ########.fr       */
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

static const t_option		g_options[] = {
	(t_option){
		.option = {"help", "h"},
		.type = {OPT_DOUBLE, OPT_SINGLE},
		.length = 2,
		.match = (t_opt_match){
			.func = &help,
			.arg_count = 0,
			.desc = "Show this usage."
		},
	},
	(t_option){
		.option = {"dump", "d"},
		.type = {OPT_SINGLE, OPT_SINGLE},
		.length = 2,
		.match = (t_opt_match){
			.func = &set_dump,
			.types = {BBOA_AT_INTEGER},
			.arg_count = 1,
			.desc = DESC_DUMP "If set to -1 prints at the end of the game.",
		},
	},
	(t_option){
		.option = {"dump-size", "ds"},
		.type = {OPT_DOUBLE, OPT_SINGLE},
		.length = 2,
		.match = (t_opt_match){
			.func = &set_dump_size,
			.types = {BBOA_AT_INTEGER},
			.arg_count = 1,
			.desc = DESC_DS
		},
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
		},
	},
	(t_option){
		.option = {"v", "visu"},
		.type = {OPT_SINGLE, OPT_DOUBLE},
		.length = 2,
		.match = (t_opt_match){
			.func = &load_visu,
			.arg_count = 0,
			.desc = "Sets viewer mode."
		},
	},
	(t_option){
		.option = {"db", "dbg", "debug"},
		.type = {OPT_SINGLE, OPT_SINGLE, OPT_DOUBLE},
		.length = 3,
		.match = (t_opt_match){
			.func = &set_vm_debug,
			.arg_count = 0,
			.desc = "Prints debug messages."
		},
	},
};

static inline char			**parse_options(int c, char **v, void *data)
{
	static t_opt_patterns	patterns;
	uint32_t				i;
	uint32_t				j;

	patterns = (t_opt_patterns){.data = data,
		.mapd = ft_hashmap_create(),
		.maps = ft_hashmap_create(),
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
		bboa_set_error_usage(&patterns, NULL, BBOA_RS_DISPLAY_USAGE,
				BBOA_ERR_NO);
		bboa_print_error(g_bboa_error);
	}
	return (bboa_parse_args(&patterns, c, v));
}

static inline bool			append_champion(char *path)
{
	int						i;

	i = 0;
	while (i < 4)
		if (!g_vm.warriors[i].id)
		{
			if (corewar_load_warriors(i, path))
				return (false);
			else
				i++;
		}
		else
			i++;
	return (i < 4);
}

static inline bool			parse_args(int c, char **v)
{
	int						i;
	int						j;
	bool					error;

	++v;
	i = parse_options(--c, v, &g_vm) - v;
	if (i < c && ft_strequ(v[i], "--"))
		i++;
	j = 0;
	error = false;
	while (!error && i + j < c)
	{
		if ((error = append_champion(v[i + j])))
			break ;
		j++;
	}
	return (error);
}

int							main(int c, char **v)
{
	bool					error;

	error = parse_args(c, v);
	print_warriors();
	if (error)
		print_vm((t_print){.level = LOG_WARN, .printer = printer,
				.data = "Too much champions in arguments, ignoring...\n"});
	if (!g_vm.warriors_nb)
		print_vm((t_print){.level = LOG_CRIT, .printer = printer,
				.data = "No valid champion loaded in the vm, exiting...\n"});
	if (g_vm.warriors_nb > 1 || g_vm.visu.used)
	{
		corewar_load_arena();
		if (g_vm.visu.used)
			start_visu();
		automaton_run(&g_vm);
		if (g_vm.visu.used)
			visu_end_wait();
		if ((int32_t)g_vm.flags.dump_cycle < 0)
			print_dump(&g_vm);
	}
	print_the_winner();
	return (0);
}
