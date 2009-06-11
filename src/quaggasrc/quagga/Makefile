include ../../../Makefile.inc
ifeq ($(MODE),debug)
CFLAGS=-g -Wall
else
CFLAGS=-O2
endif

INCLUDES = -I. -I./lib -I../..

CFLAGS += $(INCLUDES) -DHAVE_CONFIG_H -fPIC -Wimplicit -fexceptions

all: libdir ripddir zebradir ospfdir bgpddir globalvars.o

libdir:
	(cd lib; make)

ripddir:
	(cd ripd; make)

zebradir:
	(cd zebra; make)

ospfdir:
	(cd ospfd; make)

bgpddir:
	(cd bgpd; make)

clean:
	(cd lib; make clean)
	(cd ripd; make clean)
	(cd zebra; make clean)
	(cd ospfd; make clean)
	(cd bgpd; make clean)
	rm -f globalvars.o

