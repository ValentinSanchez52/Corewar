#include <assert.h>
#include <stddef.h>
#include "tests.h"
#include "corewar.h"

static t_utest		*tests[] = {
	&utest_ld,
};

int				main(void)
{
	for (size_t i = 0; i < sizeof(tests) / sizeof(void (*)(void)); i++)
		tests[i]();
}
