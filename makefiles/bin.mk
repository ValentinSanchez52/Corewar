#==============================================================================#
#                                 Flags detection                              #
#==============================================================================#

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LDFLAGS+= 
else ifeq ($(UNAME_S),Darwin)
endif

ifeq ($(UNAME_S),Linux)
LDFLAGS+=$(foreach lib, $(SYSLIBS_LINUX), -l$(lib)) $(LDFLAGS_LINUX)
else ifeq ($(UNAME_S),Darwin)
LDFLAGS+=$(foreach lib, $(SYSLIBS_DARWIN), -l$(lib)) $(LDFLAGS_DARWIN)
endif
LDFLAGS+=$(foreach lib, $(SYSLIBS), -l$(lib))

#==============================================================================#
#                               Binary compilation                             #
#==============================================================================#

$(NAME): $(CLIBS) $(OBJS)
	@printf $(START_MSG)
	@printf $(MAKING_PROGRESS)
	@$(CC) $(LDFLAGS) $(LDLIBS) $(CFLAGS) $^ -o $(NAME) ; \
		if [ "$$?" != "1" ]; then \
			printf $(MAKING_SUCCESS); \
			exit 0; \
		else \
			printf $(MAKING_FAILURE); \
			exit 2; \
		fi
	@chmod +x $(NAME)
