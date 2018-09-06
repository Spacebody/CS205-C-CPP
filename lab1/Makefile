# Copyright (c) Yilin Zheng Sept. 6, 2018.

CC	              = gcc
CFLAGS            = -I.

DEPS = distance.h
OBJ  = distance.o
LIBS = -lm

%.o : %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)

cal_distance: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
	-rm -f *.o cal_distance