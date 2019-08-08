# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 18:27:52 by mbeilles          #+#    #+#              #
#    Updated: 2019/08/08 19:14:08 by mbeilles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
-include ./strings.mk

PATH_TEST ?= tests
TEST_ENTRY_POINT ?= main.c

ifeq (NO_TEST_FILES,)
$(call assert,$(TESTS),Test files are undefined, cannot run tests...)
else
TEST_OBJS := $(patsubst %.c, $(PATH_OBJ)/%.o, $(TESTS) $(filter-out $(PATH_SRC)/main.c,$(SRCS)))
endif

CFLAGS += $(FAST_FLAG)

test: $(TEST_OBJS) $(CLIBS)
	@printf $(COMPILING_TEST)
	@$(CC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) -o test $^ \
		$(PATH_TEST)/$(TEST_ENTRY_POINT); \
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
