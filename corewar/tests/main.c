#include <assert.h>
#include <stddef.h>
#include "tests.h"
#include "corewar.h"

static t_utest		*tests[] = {
	&utest_ld,
	&utest_st,
};

t_vm				g_vm = (t_vm){};

int				main(void)
{
	bool		error = false;

	for (size_t i = 0; i < sizeof(tests) / sizeof(void (*)(void)); i++)
		error |= tests[i]();
	assert(!error);
}
