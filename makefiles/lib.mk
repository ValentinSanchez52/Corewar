$(NAME): $(CLIBS) $(OBJS)
	@printf $(WOW)"\n"
	@printf $(START_MSG)
	@printf $(MAKING_PROGRESS)
	@ar -rc $@ $(OBJS); \
		if [ "$$?" != "1" ]; then \
			printf $(MAKING_SUCCESS); \
			exit 0; \
		else \
			printf $(MAKING_FAILURE); \
			exit 2; \
		fi
	@chmod +x $(NAME)
