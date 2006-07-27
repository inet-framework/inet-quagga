# Makefile


include ../../../../inetconfig

AODVDIR=$(shell pwd)


SRC_OMNET = 	debug.c list.c timer_queue.c aodv_socket.c aodv_hello.c \
		aodv_neighbor.c aodv_timeout.c routing_table.c seek_list.c \
		aodv_rreq.c aodv_rrep.c aodv_rerr.c locality.c

SRC_OMNET_CPP =	

OBJS_OMNET = $(SRC_OMNET:%.c=%.o)
OBJS_OMNET_CPP = 


INCLUDE_PATH= -I. -I../../../../Transport/Contract -I../../../Contract -I../../../../NetworkInterfaces/Contract -I../../../../Base -I../../../../Util -I../../../IPv4 -I../../../Contract -I../../../AutoRouting -I../../../Queue  -I../../../../Transport/UDP -I../../../../NetworkInterfaces -I../../../../Nodes/INET -I../Aodv -I$(OMNETPP_INCL_DIR)

KERNEL=$(shell uname -r)
# Change to compile against different kernel (can be overridden):
KERNEL_DIR=/lib/modules/$(KERNEL)/build
KERNEL_INC=$(KERNEL_DIR)/include

# Compiler and options:
CC=gcc
LD=ld
CPP=g++
OPTS=-Wall 
CPP_OPTS=

export CC

# Comment out to disable debug operation...
DEBUG=-g3 -DDEBUG
# Add extra functionality. Uncomment or use "make XDEFS=-D<feature>" on 
# the command line.
XDEFS=
DEFS=#-DCONFIG_GATEWAY #-DLLFEEDBACK
CFLAGS=$(OPTS) $(DEBUG) $(DEFS) $(XDEFS)
LD_OPTS=

ifneq (,$(findstring CONFIG_GATEWAY,$(DEFS)))
SRC:=$(SRC) locality.c
endif
ifneq (,$(findstring LLFEEDBACK,$(DEFS)))
SRC:=$(SRC) llf.c
LD_OPTS:=$(LD_OPTS) -liw
endif

# ARM specific configuration goes here:
#=====================================
ARM_INC=

# OMNET specific configuration goes here:
#=====================================
OMNET_DEFS= -DOMNETPP -DNS_PORT

# Set extra DEFINES here. Link layer feedback is now a runtime option.
EXTRA_OMNET_DEFS=

ifneq (,$(findstring CONFIG_GATEWAY,$(EXTRA_OMNET_DEFS)))
SRC_OMNET:=$(SRC_OMNET) locality.c
endif

include ../../../../inetconfig

# Note: OPTS is overridden by OMNET Makefile
OMNET_CFLAGS=$(OPTS) $(CPP_OPTS) $(DEBUG) $(OMNET_DEFS) $(EXTRA_OMNET_DEFS)

OMNET_INC= $(INCLUDE_PATH) # 

OMNET_TARGET=libaodv-uu.a

# Archiver and options
AR=ar
AR_FLAGS=rc

.PHONY: default clean install uninstall depend tags aodvd-arm docs kaodv kaodv-arm kaodv-mips

default: $(OMNET_TARGET)

endian.h:
	$(CC) $(CFLAGS) -o endian endian.c
	./endian > endian.h

$(OBJS): %.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJS_OMNET): %.o: %.c Makefile
	$(CPP) $(OMNET_CFLAGS) $(OMNET_INC) -c -o $@ $<

$(OBJS_OMNET_CPP): %-ns.o: %.cc Makefile
	$(CPP) $(OMNET_CFLAGS) $(OMNET_INC) -c -o $@ $<

aodvd: $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LD_OPTS)

$(OMNET_TARGET): $(OBJS_OMNET_CPP) $(OBJS_OMNET) endian.h 
	$(AR) $(AR_FLAGS) $@ $(OBJS_OMNET_CPP) $(OBJS_OMNET) > /dev/null

tags:
	etags *.c *.h
indent:
	indent -kr -l 80 *.c \
	$(filter-out $(SRC_OMNET_CPP:%.cc=%.h),$(wildcard *.h))
	$(MAKE) -C lnx indent
depend:
	@echo "Updating Makefile dependencies..."
	@makedepend -Y./ -- $(DEFS) -- $(SRC) &>/dev/null
	@makedepend -a -Y./ -- $(KDEFS) kaodv.c &>/dev/null

install: default
	install -s -m 755 aodvd /usr/sbin/aodvd
	@if [ ! -d /lib/modules/$(KERNEL)/aodv ]; then \
		mkdir /lib/modules/$(KERNEL)/aodv; \
	fi

	@echo "Installing kernel module in /lib/modules/$(KERNEL)/aodv/";
	@if [ -f ./kaodv.ko ]; then \
		install -m 644 kaodv.ko /lib/modules/$(KERNEL)/aodv/kaodv.ko; \
	else \
		install -m 644 kaodv.o /lib/modules/$(KERNEL)/aodv/kaodv.o; \
	fi
	/sbin/depmod -a
uninstall:
	rm -f /usr/sbin/aodvd
	rm -rf /lib/modules/$(KERNEL)/aodv

docs:
	cd docs && $(MAKE) all
clean: 
	rm -f aodvd *~ *.o core *.log $(OMNET_TARGET) endian endian.h ns/*.o ns/*~
	cd lnx && $(MAKE) clean
#cd docs && $(MAKE) clean

# DO NOT DELETE

main.o: defs.h timer_queue.h list.h debug.h params.h aodv_socket.h
main.o: aodv_rerr.h routing_table.h aodv_timeout.h k_route.h aodv_hello.h
main.o: aodv_rrep.h nl.h
list.o: list.h
debug.o: aodv_rreq.h defs.h timer_queue.h list.h seek_list.h routing_table.h
debug.o: aodv_rrep.h aodv_rerr.h debug.h params.h
timer_queue.o: timer_queue.h defs.h list.h debug.h
aodv_socket.o: aodv_socket.h defs.h timer_queue.h list.h aodv_rerr.h
aodv_socket.o: routing_table.h params.h aodv_rreq.h seek_list.h aodv_rrep.h
aodv_socket.o: aodv_hello.h aodv_neighbor.h debug.h
aodv_hello.o: aodv_hello.h defs.h timer_queue.h list.h aodv_rrep.h
aodv_hello.o: routing_table.h aodv_timeout.h aodv_rreq.h seek_list.h params.h
aodv_hello.o: aodv_socket.h aodv_rerr.h debug.h
aodv_neighbor.o: aodv_neighbor.h defs.h timer_queue.h list.h routing_table.h
aodv_neighbor.o: aodv_rerr.h aodv_hello.h aodv_rrep.h aodv_socket.h params.h
aodv_neighbor.o: debug.h
aodv_timeout.o: defs.h timer_queue.h list.h aodv_timeout.h aodv_socket.h
aodv_timeout.o: aodv_rerr.h routing_table.h params.h aodv_neighbor.h
aodv_timeout.o: aodv_rreq.h seek_list.h aodv_hello.h aodv_rrep.h debug.h
aodv_timeout.o: k_route.h nl.h
routing_table.o: routing_table.h defs.h timer_queue.h list.h aodv_timeout.h
routing_table.o: aodv_rerr.h aodv_hello.h aodv_rrep.h aodv_socket.h params.h
routing_table.o: k_route.h debug.h seek_list.h nl.h
seek_list.o: seek_list.h defs.h timer_queue.h list.h aodv_timeout.h params.h
seek_list.o: debug.h
k_route.o: defs.h timer_queue.h list.h debug.h k_route.h
aodv_rreq.o: aodv_rreq.h defs.h timer_queue.h list.h seek_list.h
aodv_rreq.o: routing_table.h aodv_rrep.h aodv_timeout.h k_route.h
aodv_rreq.o: aodv_socket.h aodv_rerr.h params.h debug.h locality.h
aodv_rrep.o: aodv_rrep.h defs.h timer_queue.h list.h routing_table.h
aodv_rrep.o: aodv_neighbor.h aodv_hello.h aodv_timeout.h aodv_socket.h
aodv_rrep.o: aodv_rerr.h params.h debug.h
aodv_rerr.o: aodv_rerr.h defs.h timer_queue.h list.h routing_table.h
aodv_rerr.o: aodv_socket.h params.h aodv_timeout.h debug.h
nl.o: defs.h timer_queue.h list.h lnx/kaodv-netlink.h debug.h aodv_rreq.h
nl.o: seek_list.h routing_table.h aodv_timeout.h aodv_hello.h aodv_rrep.h
nl.o: params.h
locality.o: locality.h defs.h timer_queue.h list.h debug.h

generateheaders: # target invoked by OMNeT++-generated uplevel Makefile.vc; does nothing for now

depend:	# target invoked by OMNeT++-generated uplevel Makefile.vc; does nothing for now

