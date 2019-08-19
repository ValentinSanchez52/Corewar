#include <assert.h>
#include <stdio.h>
#include "corewar.h"
#include "print.h"

struct				ld_test {
	char			*desc;
	t_process		value;
	t_process		result;
};

bool				utest_ld(void)
{
	struct ld_test	processes[] = {

		(struct ld_test){
			.desc = "Load 0x42 in register 1",
			.value = (t_process){
				.uuid = "none",
				.registers = {},
				.op = (t_op){
					.code = COR_OP_LOAD,
					.types = {COR_ARG_DIR, COR_ARG_REG},
					.args = {0x42, 0x1},
					.param_count = 2,
				},
			},
			.result = (t_process){
				.uuid = "none",
				.registers = {
					[0] = 0x42,
				},
				.op = (t_op){
					.code = COR_OP_LOAD,
					.types = {COR_ARG_DIR, COR_ARG_REG},
					.args = {0x42, 0x1},
					.param_count = 2,
				},
			},
		},

		(struct ld_test){
			.desc = "Load form arena [addr: 46](0x00000056) to register 1",
			.value = (t_process){
				.uuid = "none",
				.registers = {},
				.op = (t_op){
					.code = COR_OP_LOAD,
					.types = {COR_ARG_IND, COR_ARG_REG},
					.args = {46, 0x1},
					.param_count = 2,
				},
			},
			.result = (t_process){
				.uuid = "none",
				.registers = {[0] = 0x56},
				.op = (t_op){
					.code = COR_OP_LOAD,
					.types = {COR_ARG_IND, COR_ARG_REG},
					.args = {46, 0x1},
					.param_count = 2,
				},
			},
		},

		(struct ld_test){
			.desc = "Load 46 in register 4",
			.value = (t_process){
				.uuid = "none",
				.registers = {},
				.op = (t_op){
					.code = COR_OP_LOAD,
					.types = {COR_ARG_DIR, COR_ARG_REG},
					.args = {46, 0x4},
					.param_count = 2,
				},
			},
			.result = (t_process){
				.uuid = "none",
				.registers = {[3] = 46},
				.op = (t_op){
					.code = COR_OP_LOAD,
					.types = {COR_ARG_DIR, COR_ARG_REG},
					.args = {46, 0x4},
					.param_count = 2,
				},
			},
		},

	};

	bool	error = false;

	g_vm = (t_vm){
		.arena = {
			[46] = 0x0,
			[47] = 0x0,
			[48] = 0x0,
			[49] = 0x56,
		},
	};

	printf("[\e[1;33m%s\e[0m] Syntax: \e[31m-\e[0m : expected, \e[32m+\e[0m : returned\n", __FILE__);
	for (size_t i = 0; i < sizeof(processes) / sizeof(struct ld_test); i++)
	{
		op_ld(&processes[i].value);
		if (memcmp(&processes[i].value, &processes[i].result, sizeof(t_process)) == 0) {
			printf("[\e[1;32m + \e[0m] [\e[1;33m%02zx\e[0m] \e[1;32mPassed!\e[0m\n", i + 1);
		} else {
			error = true;

			printf("[\e[1;31m x \e[0m] [\e[1;33m%02zx\e[0m] \e[1;31mFailed:\e[0m %s in \e[4m%s\e[0m\n", i + 1, processes[i].desc, __FILE__);
			printf("\e[31m----- ");
			fflush(stdout);
			print_op(&processes[i].result, true);
			printf("\e[32m+++++ ");
			fflush(stdout);
			print_op(&processes[i].value, true);
			printf("\e[31m----- ");
			fflush(stdout);
			print_process(&processes[i].result, true);
			printf("\e[32m+++++ ");
			fflush(stdout);
			print_process(&processes[i].value, true);
			printf("\n");
		}
	}
	if (!error)
		printf("\n");
	return (error);
}
