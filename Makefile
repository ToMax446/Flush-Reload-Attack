FILES=$(wildcard *.c)
TARGETS=$(FILES:.c=)
OBJS=${FILES:.c=.o}
CFLAGS=-g -std=gnu99 -I../src `pkg-config --cflags gtk+-3.0`
LDFLAGS=-L../src/ -g `pkg-config --libs gtk+-3.0`
LDLIBS=-lmastik
TCFLAGS=-g -Wall -Wextra `pkg-config --cflags gtk+-3.0`
TLDFLAGS=`pkg-config --libs gtk+-3.0`




all: ${TARGETS}

${TARGETS}: %: %.o 
	${CC} ${LDFLAGS} -o $@ $@.o ${LDLIBS} 

target: target.o
	gcc $(TCFLAGS) target.c $(TLDFLAGS) -o target

clean:
	rm -f ${TARGETS} ${OBJS} *.sig out *.json

distclean: clean
	rm Makefile
