default:
	@echo "Please choose a target (e.g. test0)\n"

test0: test0.c input.h
	gcc -O2 -pipe -o test0 test0.c
test0pp: test0.c input.h
	gcc -E -pipe -o test0.c.pp test0.c

test1: test1.c input.h
	gcc -O2 -pipe -o test1 test1.c
test1pp: test1.c input.h
	gcc -E -pipe -o test1.c.pp test1.c

test2: test2.c input.h
	gcc -O2 -pipe -o test2 test2.c
test2pp: test2.c input.h
	gcc -E -pipe -o test2.c.pp test2.c
