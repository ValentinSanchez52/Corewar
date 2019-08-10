# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 18:27:52 by mbeilles          #+#    #+#              #
#    Updated: 2019/08/09 15:20:12 by mbeilles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
-include ./strings.mk

# Ensures defaults so you don't have to.
PATH_TEST ?= tests
TEST_ENTRY_POINT ?= $(PATH_TEST)/main.c
PROG_ENTRY_POINT ?= $(PATH_SRC)/main.c

ifeq (NO_TEST_FILES,)
# If there is no tests to be compiled without specifing NO_TEST_FILES
# Then there is a problem and the test rule should be aborted.
$(call assert,$(TESTS),Test files are undefined, cannot run tests...)
else
# Gets all tests files for the conversion with the tests entry point
# Then gets all program sources excepts it's entry point
TEST_OBJS := $(patsubst %.c, $(PATH_OBJ)/%.o, $(TESTS) $(TEST_ENTRY_POINT)) \
	$(patsubst %.c, $(PATH_OBJ)/%.o, $(filter-out $(PROG_ENTRY_POINT),$(SRCS)))
endif

CFLAGS += $(SLOW_FLAG) # Sets the debug flags for finding any underlying segfault.

test: $(TEST_OBJS) $(CLIBS)
	@echo $(TEST_OBJS)
	@printf $(COMPILING_TEST)
	@$(CC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) -o test $^ ; \
		if [ "$$?" != "1" ]; then \
			printf $(MAKING_SUCCESS); \
			exit 0; \
		else \
			printf $(MAKING_FAILURE); \
			exit 2; \
		fi
	@chmod +x test
	@printf $(TESTING)
	@./test

.PHONY: test
