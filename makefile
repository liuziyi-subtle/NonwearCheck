ROOTDIR = $(CURDIR)
CC = gcc -g
CFLAGS = -O -Wall -Wextra -Wl,-rpath=$(ROOTDIR)

ETOBJS = main.o nonwear_check.o nonwear_model_green.o nonwear_model_ir.o \
         nonwear_arm_bitreversal2.o nonwear_arm_rfft_fast_f64.o \
				 nonwear_arm_rfft_fast_init_f64.o nonwear_arm_cfft_f64.o \
				 nonwear_ar_solver.o

all:	main

main: $(ETOBJS)
	$(CC) -o main $(ETOBJS) -Wall -lm -DDEBUG_LOCAL=1

main.o: main.c nonwear_check.h
	$(CC) -c main.c -DDEBUG_LOCAL=1

nonwear_check.o: nonwear_check.c nonwear_check.h
	$(CC) -c nonwear_check.c -DDEBUG_LOCAL=1

nonwear_model_green.o: nonwear_model_green.c nonwear_model.h
	$(CC) -c nonwear_model_green.c -DDEBUG_LOCAL=1

nonwear_model_ir.o: nonwear_model_ir.c nonwear_model.h
	$(CC) -c nonwear_model_ir.c -DDEBUG_LOCAL=1

nonwear_arm_bitreversal2.o: nonwear_arm_bitreversal2.c
	$(CC) -c nonwear_arm_bitreversal2.c -DDEBUG_LOCAL=1

nonwear_arm_rfft_fast_f64.o: nonwear_arm_rfft_fast_f64.c nonwear_arm_rfft_fast_f64.h
	$(CC) -c nonwear_arm_rfft_fast_f64.c -DDEBUG_LOCAL=1

nonwear_arm_rfft_fast_init_f64.o: nonwear_arm_rfft_fast_init_f64.c nonwear_arm_rfft_fast_f64.h
	$(CC) -c nonwear_arm_rfft_fast_init_f64.c -DDEBUG_LOCAL=1

nonwear_arm_cfft_f64.o: nonwear_arm_cfft_f64.c
	$(CC) -c nonwear_arm_cfft_f64.c -DDEBUG_LOCAL=1

nonwear_ar_solver.o: nonwear_ar_solver.c nonwear_ar_solver.h
	$(CC) -c nonwear_ar_solver.c -DDEBUG_LOCAL=1

clean:
	rm -f *.o *.out *~ main
