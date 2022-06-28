# Makefile for sample_main

PROGRAM	:=	program.out
SRCS	:=	sample_main.c singly-linked_list.c
OBJS	:=	${SRCS:.c=.o}
CC		:=	gcc
CCFLAGS	:=	-g -Wall -Wextra -pedantic
LINKER	:=	ld -lc

.SUFFIXES: .o .c

.c.o:
	@$(CC) $(CCFLAGS) -c $< -o $@

$(PROGRAM):	$(OBJS)
	@echo "Loading $@ ... "
	@$(LINKER) $^ -o $@
	@echo "done"

.PHONY: all
all:	$(PROGRAM)

.PHONY:	exec
exec:	all
	@./${PROGRAM}

.PHONY: clean
clean:
	@rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	@rm -f $(PROGRAM)
