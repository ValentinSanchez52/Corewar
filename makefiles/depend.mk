-include ./strings.mk
.PRECIOUS: $(PATH_OBJ)/. $(PATH_OBJ)%/.

$(PATH_OBJ)/.:
	@printf $(CREATE_DIR) $(PATH_OBJ)
	@mkdir -p $@

$(PATH_OBJ)%/.:
	@printf $(CREATE_SUBDIR) $(dir $(patsubst %/., %, $@)) $(notdir $(patsubst %/., %, $@))
	@mkdir -p $@

$(PATH_DEP)/.:
	@printf $(CREATE_DIR) $(PATH_DEP)
	@mkdir -p $@

$(PATH_DEP)%/.:
	@printf $(CREATE_SUBDIR) $(dir $(patsubst %/., %, $@)) $(notdir $(patsubst %/., %, $@))
	@mkdir -p $@

libraries = $(shell make -q -s -C $(1) || echo 'FORCE')

-include $(DEPS)
.PRECIOUS: $(DEPS)

#==============================================================================#
#                                 Dependencies                                 #
#==============================================================================#

$(PATH_DEP)/%.d: ;

.SECONDEXPANSION:

FAST_FLAG = -O3 -march=native -flto
SLOW_FLAG = -fsanitize=address -g3 -O0

ifeq	(,$(filter debug, $(MAKECMDGOALS)))
CFLAGS += $(FAST_FLAG)
START_MSG = $(COMPILING_PRD)
else
CFLAGS += $(SLOW_FLAG)
START_MSG = $(COMPILING_DBG)
endif

debug: $(NAME)

FORCE:

depend:
	@for lib in $(foreach clib,$(CLIBS),$(dir $(clib))); do \
		printf $(MAKING_LIB) $${lib%/} ; \
		$(MAKE) -C $$lib $(MAKECMDGOALS) --no-print-directory MASTERLIBS="$(MASTERLIBS)$(CLIBS)"; \
	done
	@printf $(MADE_LIB)

ifneq ($(CLIBS), )
$(CLIBS): $$(strip $$(call libraries,$$(@D)))
	@printf $(MAKING_LIB) $(basename $(notdir $@))
	@$(MAKE) -C $(@D) --no-print-directory $(MAKECMDGOALS)
endif

$(PATH_OBJ)/%.o: %.c | $$(@D)/. $(PATH_DEP)/$$(*D)/. $$(LDLIBS) $$(CLIBS)
$(PATH_OBJ)/%.o: %.c $(PATH_DEP)/%.d | $$(@D)/. $(PATH_DEP)/$$(*D)/. $$(LDLIBS) $$(CLIBS)
	@$(CC) $(CFLAGS) -MT $@ -MMD -MP -MF $(PATH_DEP)/$*.Td -c $< -o $@; \
		if [ "$$?" != "1" ]; then \
			printf $(COMPILING_OK); exit 0; \
		else \
			printf $(COMPILING_KO); exit 2; \
		fi
	@mv -f $(PATH_DEP)/$*.Td $(PATH_DEP)/$*.d
	@touch $@

