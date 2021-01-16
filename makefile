CC = $(Compiler) -g
CFLAGS = -Wall -Wextra

# 0 - 单条数据  1 - 多个文件
DFLAGS = -DALGO_DEBUG=0

DIR_DEBUG = debug

DIR_RESULTS = results

ETOBJS = main.o nonwear_check.o nonwear_model_green.o nonwear_model_ir.o

all:	$(DIR_RESULTS) executable

$(DIR_RESULTS):
	mkdir $@

executable: $(ETOBJS)
	$(CC) $(CFLAGS) -o $@ $(ETOBJS) -Wall -lm

main.o:
	$(CC) $(CFLAGS) -c $(DIR_DEBUG)/main.c -o $@ -I$(DIR_DEBUG) $(DFLAGS)

nonwear_check.o:
	$(CC) $(CFLAGS) -c nonwear_check.c $(DFLAGS)

nonwear_model_green.o:
	$(CC) $(CFLAGS) -c nonwear_model_green.c $(DFLAGS)

nonwear_model_ir.o:
	$(CC) $(CFLAGS) -c nonwear_model_ir.c $(DFLAGS)

debug.o:
	$(CC) $(CFLAGS) -c $(DIR_DEBUG)/debug.c -o $@ -I$(DIR_DEBUG) $(DFLAGS)

clean:
	rm -rf *.o *.out *~ executable $(DIR_RESULTS)







# ROOTDIR = $(CURDIR)
# CC = gcc -g
# CFLAGS = -O -Wall -Wextra -Wl,-rpath=$(ROOTDIR)

# ETOBJS = main.o nonwear_check.o nonwear_model_green.o nonwear_model_ir.o
#         #  nonwear_conv.o nonwear_arm_bitreversal2.o nonwear_arm_rfft_fast_f64.o \
# 				#  nonwear_arm_rfft_fast_init_f64.o nonwear_arm_cfft_f64.o

# all:	main

# main: $(ETOBJS)
# 	$(CC) -o main $(ETOBJS) -Wall -lm -DDEBUG_LOCAL=1

# main.o: main.c nonwear_check.h
# 	$(CC) -c main.c -DDEBUG_LOCAL=1

# nonwear_check.o: nonwear_check.c nonwear_check.h
# 	$(CC) -c nonwear_check.c -DDEBUG_LOCAL=1

# nonwear_model_green.o: nonwear_model_green.c nonwear_model.h
# 	$(CC) -c nonwear_model_green.c -DDEBUG_LOCAL=1

# nonwear_model_ir.o: nonwear_model_ir.c nonwear_model.h
# 	$(CC) -c nonwear_model_ir.c -DDEBUG_LOCAL=1

# # nonwear_conv.o: nonwear_conv.c nonwear_conv.h
# # 	$(CC) -c nonwear_conv.c -DDEBUG_LOCAL=1

# # nonwear_arm_bitreversal2.o: nonwear_arm_bitreversal2.c
# # 	$(CC) -c nonwear_arm_bitreversal2.c -DDEBUG_LOCAL=1

# # nonwear_arm_rfft_fast_f64.o: nonwear_arm_rfft_fast_f64.c nonwear_arm_rfft_fast_f64.h
# # 	$(CC) -c nonwear_arm_rfft_fast_f64.c -DDEBUG_LOCAL=1

# # nonwear_arm_rfft_fast_init_f64.o: nonwear_arm_rfft_fast_init_f64.c nonwear_arm_rfft_fast_f64.h
# # 	$(CC) -c nonwear_arm_rfft_fast_init_f64.c -DDEBUG_LOCAL=1

# # nonwear_arm_cfft_f64.o: nonwear_arm_cfft_f64.c
# # 	$(CC) -c nonwear_arm_cfft_f64.c -DDEBUG_LOCAL=1


# clean:
# 	rm -f *.o *.out *~ main
