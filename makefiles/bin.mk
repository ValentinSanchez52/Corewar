$(NAME): $(CLIBS) $(OBJS)
	@printf $(START_MSG)
	@printf $(MAKING_PROGRESS)
	@$(CC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) -o $(NAME) $^; \
		if [ "$$?" != "1" ]; then \
			printf $(MAKING_SUCCESS); \
			exit 0; \
		else \
			printf $(MAKING_FAILURE); \
			exit 2; \
		fi
	@chmod +x $(NAME)
