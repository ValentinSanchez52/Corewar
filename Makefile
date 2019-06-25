corewar:
	@$(MAKE) -C corewar $(MAKECMDGOALS)

asm:
	@$(MAKE) -C asm $(MAKECMDGOALS)

all: corewar asm
re: corewar asm
clean: corewar asm
fclean: corewar asm
depend: corewar asm

.PHONY: all re corewar asm clean fclean depend
