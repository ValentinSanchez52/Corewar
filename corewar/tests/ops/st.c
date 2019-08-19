/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 14:39:55 by mbeilles          #+#    #+#             */
/*   Updated: 2019/08/19 16:43:55 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "corewar.h"
#include "print.h"

struct				st_test {
	char			*desc;

	bool			arena_test;
	uint32_t		arena_output;
	uint32_t		arena_index;

	bool			process_test;
	t_process		process_input;
	t_process		process_output;
};

static inline void	_test_condition(
		bool condition,
		size_t i,
		uint32_t arena_input,
		struct st_test test
)
{

		if (condition) {
			printf("[\e[1;32m + \e[0m] [\e[1;33m%02zx\e[0m] \e[1;32mPassed!\e[0m\n", i + 1);
		} else {
			printf("[\e[1;31m x \e[0m] [\e[1;33m%02zx\e[0m] \e[1;31mFailed:\e[0m %s in \e[4m%s\e[0m\n", i + 1, test.desc, __FILE__);

			if (test.process_test) {
				printf("\e[31m----- ");
				fflush(stdout);
				print_op(&test.process_output, true);
				printf("\e[32m+++++ ");
				fflush(stdout);
				print_op(&test.process_input, true);
				printf("\e[31m----- ");
				fflush(stdout);
				print_process(&test.process_output, true);
				printf("\e[32m+++++ ");
				fflush(stdout);
				print_process(&test.process_input, true);
			}
			if (test.arena_test) {
				uint32_t index = test.arena_index
						+ test.process_output.global_offset
						+ test.process_output.pc;
				printf("\e[31m----- \e[0mArena: [idx: %02x] [value: %02x]\n", index, test.arena_output);
				printf("\e[32m+++++ \e[0mArena: [idx: %02x] [value: %02x]\n", index, arena_input);
			}
			printf("\n");
		}
}

bool				utest_st(void)
{
	struct st_test	processes[] = {

		(struct st_test){
			.desc = "Stores contents of register 2 (0x42) into register 2",

			.process_test = true,
			.process_input = (t_process){
				.uuid = "none",
				.registers = {[1] = 0x42},
				.op = (t_op){
					.code = COR_OP_STORE,
					.types = {COR_ARG_REG, COR_ARG_REG},
					.args = {0x2, 0x2},
					.param_count = 2,
				},
			},
			.process_output = (t_process){
				.uuid = "none",
				.registers = {[1] = 0x42},
				.op = (t_op){
					.code = COR_OP_STORE,
					.types = {COR_ARG_REG, COR_ARG_REG},
					.args = {0x2, 0x2},
					.param_count = 2,
				},
			},
		},

		(struct st_test){
			.desc = "Stores contents of register 1 (0xbb) into register 2",

			.process_test = true,
			.process_input = (t_process){
				.uuid = "none",
				.registers = {[0] = 0xbb, [2] = 0x55},
				.op = (t_op){
					.code = COR_OP_STORE,
					.types = {COR_ARG_REG, COR_ARG_REG},
					.args = {0x1, 0x2},
					.param_count = 2,
				},
			},
			.process_output = (t_process){
				.uuid = "none",
				.registers = {[0] = 0xbb, [1] = 0xbb, [2] = 0x55},
				.op = (t_op){
					.code = COR_OP_STORE,
					.types = {COR_ARG_REG, COR_ARG_REG},
					.args = {0x1, 0x2},
					.param_count = 2,
				},
			},
		},

		(struct st_test){
			.desc = "Stores contents of register 4 (0x42)",

			.arena_test = true,
			.arena_index = 0x67,
			.arena_output = 0x42,

			.process_test = true,
			.process_input = (t_process){
				.uuid = "none",
				.registers = {[3] = 0x42},
				.op = (t_op){
					.code = COR_OP_STORE,
					.types = {COR_ARG_REG, COR_ARG_IND},
					.args = {0x4, 0x67},
					.param_count = 2,
				},
			},
			.process_output = (t_process){
				.uuid = "none",
				.registers = {[3] = 0x42},
				.op = (t_op){
					.code = COR_OP_STORE,
					.types = {COR_ARG_REG, COR_ARG_IND},
					.args = {0x4, 0x67},
					.param_count = 2,
				},
			},
		},

	};
	bool	error = false;

	// Clean and init vm
	g_vm = (t_vm){.arena = {[87] = 2}};

	printf("[\e[1;33m%s\e[0m] Syntax: \e[31m-\e[0m : expected, \e[32m+\e[0m : returned\n", __FILE__);
	for (size_t i = 0; i < sizeof(processes) / sizeof(struct st_test); i++)
	{
		op_st(&processes[i].process_input);
		bool ret = false;
		uint32_t mem_value = 0;
		if (processes[i].arena_test) {
			mem_value = get_mem_value(processes[i].arena_index
					+ processes[i].process_output.global_offset
					+ processes[i].process_output.pc,
					4);
			ret |= (mem_value != processes[i].arena_output);
		}
		if (processes[i].process_test) {
			ret |= memcmp(&processes[i].process_input, &processes[i].process_output, sizeof(t_process));
		}
		_test_condition(!ret, i, mem_value, processes[i]);
		if (ret) { error = true; }
	}
	return (error);
}
