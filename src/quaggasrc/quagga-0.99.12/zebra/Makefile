include ../../../../Makefile.inc
ifeq ($(MODE),debug)
CFLAGS=-g -Wall
else
CFLAGS=-O2
endif

SOURCES = \
	zserv.c main.c interface.c connected.c zebra_rib.c \
	redistribute.c debug.c rtadv.c zebra_snmp.c zebra_vty.c \
	irdp_main.c irdp_interface.c irdp_packet.c router-id.c \
	\
	rt_netlink.c rtread_netlink.c \
	ipforward_proc.c \
	if_proc.c if_netlink.c \
	ioctl.c zebra_routemap.c \
	ioctl_null.c kernel_null.c misc_null.c redistribute_null.c

HEADERS = \
	connected.h ioctl.h rib.h rt.h zserv.h redistribute.h debug.h rtadv.h \
	interface.h ipforward.h irdp.h router-id.h kernel_socket.h

OBJECTS = \
	zserv.o main.o interface.o connected.o zebra_rib.o \
	redistribute.o debug.o rtadv.o zebra_snmp.o zebra_vty.o \
	irdp_main.o irdp_interface.o irdp_packet.o router-id.o \
	\
	rt_netlink.o rtread_netlink.o \
	ipforward_proc.o \
	if_proc.o if_netlink.o \
	ioctl.o zebra_routemap.o \
	ioctl_null.o kernel_null.o misc_null.o redistribute_null.o

INCLUDES = -I. -I.. -I../lib -I../../..

DEFS = -DHAVE_CONFIG_H -DZEBRA
CFLAGS += $(INCLUDES) $(DEFS) -fPIC -Wimplicit -fexceptions

all: zebra.a

zebra.a:  $(OBJECTS) $(HEADERS) $(SOURCES)
	ar rvs zebra.a $(OBJECTS)

clean:
	rm -f *.o *.a
