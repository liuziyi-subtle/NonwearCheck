CC=gcc -Wall -Wextra -fPIC
CUR_DIR=$(shell pwd)
LIB_INCLUDE_DIR=$(CUR_DIR)/../lib
LIB_DIR=$(CUR_DIR)/../lib
PY_INCLUDE_DIR=$(shell python3-config --includes|cut -f1 -d" ")
PY_LIB_DIR=$(shell python3-config --ldflags|cut -f1 -d" ")
PY_LIB=$(shell python3-config --libs|cut -f1 -d" ")

ETOBJS = ar_wrap.o ar.o

all:	_ar.so

# _qrs.so: qrs_wrap.o
# 	$(CC) -shared $(PY_LIB_DIR) $(PY_LIB) -L$(LIB_DIR) -lqrsdet -lwavelet -I$(LIB_INCLUDE_DIR) qrs_wrap.o -o _qrs.so

# _qrs.so: qrs_wrap.o $(ETOBJS)
# 	$(CC) -shared $(PY_LIB_DIR) $(PY_LIB) qrs_wrap.o $(ETOBJS) -o _qrs.so

_ar.so:	$(ETOBJS)
	$(CC) -shared -o _ar.so $(PY_LIB_DIR) $(PY_LIB) $(ETOBJS) -lm

ar_wrap.o:	ar_wrap.c
	$(CC) -O2 -c ar_wrap.c $(PY_INCLUDE_DIR)

ar_wrap.c:	ar.i
	swig -python ar.i

ar.o:	ar.c ar.h
	$(CC) -c ar.c

clean:	
	rm -f *_wrap.c *.py *.so *.o
