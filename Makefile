NICK = MAKE
NAME = Corewar
PROJECT_COLOR = "\033[38;5;111m"
PROJECT_COLOR_ALT = "\033[38;5;110m"

.DEFAULT_GOAL := all

CMD = $(filter-out asm, $(filter-out corewar, $(filter-out all, $(MAKECMDGOALS))))
ifeq ($(CMD),)
CMD=all
endif

corewar:
	@printf $(MAKING_COMMAND) corewar
	@$(MAKE) -C corewar $(CMD)

assembler:
	@printf $(MAKING_COMMAND) asm
	@$(MAKE) -C asm $(CMD)

all: assembler corewar
re: assembler corewar
clean: assembler corewar
fclean: assembler corewar
depend: assembler corewar

tags:
	@command -v ctags &>/dev/null && printf $(MAKING_LIB) ctags && ctags -R || printf $(DEP_NEEDED) ctags

.PHONY: all corewar assembler tags

include ./makefiles/strings.mk
