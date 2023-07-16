
TITLE_COLOR = \033[33m
NO_COLOR = \033[0m
EXTRA_CFLAGS = -Wall -Werror
UNAME := arm

DEBUG_LVL = 2
USER_APP_CONFIG = -DDEBUG_LVL=$(DEBUG_LVL)

# when excuting make, compile all exe's
all: clean
	$(Info checking if custom header is needed)
	@echo "$(TITLE_COLOR\n)***** COMPILING user_main *****$(NO_COLOR)"
ifeq ($(UNAME), x86_64)
	gcc -o user_main $(EXTRA_CFLAGS) $(USER_APP_CONFIG) -g main.c 
else
	arm-linux-gnueabihf-gcc -o user_main $(EXTRA_CFLAGS) $(USER_APP_CONFIG) -g main.c 
endif

# do not look for files called clean, clean-all or this will be always a target
.PHONY: clean
clean:
	rm -rf user_main

leak: all
	@echo "$(TITLE_COLOR)\n***** LEAK CHECK user_main *****$(NO_COLOR)"
	valgrind --leak-check=full -v --track-origins=yes --show-leak-kinds=all ./user_main

run:
	@echo "$(TITLE_COLOR)\n***** RUNNING user_app *****$(NO_COLOR)"
	./user_main