#
# OMNeT++/OMNEST Makefile for inet-quagga
#

# Main target

all:  src
	@# Do nothing

.PHONY: Makefile.inc
Makefile.inc:
	@echo "MODE=$(MODE)" >Makefile.inc

.PHONY: src
src: checkmakefiles Makefile.inc
	cd src && $(MAKE) MODE=$(MODE)

msgheaders: checkmakefiles
	cd src && $(MAKE) msgheaders

clean: checkmakefiles Makefile.inc
	-rm -rf $O
	-rm -f inet-quagga inet-quagga.exe libinet-quagga.so libinet-quagga.a libinet-quagga.dll libinet-quagga.dylib

	-cd src && $(MAKE) clean

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	-cd src && if [ -f Makefile ]; then $(MAKE) depend; fi

makefiles:
	cd src && opp_makemake -f --deep -O out -d quaggasrc -I../../inet/src/networklayer/ipv4 -I../../inet/src/networklayer/common -I../../inet/src/networklayer/rsvp_te -I../../inet/src/networklayer/icmpv6 -I../../inet/src/transport/tcp -I../../inet/src/networklayer/mpls -I../../inet/src/base -I../../inet/src/networklayer/ted -I../../inet/src/util/headerserializers -I../../inet/src/networklayer/contract -I../../inet/src/util -I../../inet/src/transport/contract -I../../inet/src/linklayer/mfcore -I../../inet/src/transport/sctp -I../../inet/src/networklayer/ipv6 -I../../inet/src/world -I../../inet/src/applications/pingapp -I../../inet/src/linklayer/contract -I../../inet/src/networklayer/arp -I../../inet/src/networklayer/ldp -I../../inet/src/transport/udp '-L../../inet/out/$$(CONFIGNAME)/src' -linet -KINET_PROJ=../../inet -- quaggasrc/quagga/globalvars.o quaggasrc/quagga/ospfd/ospfd.a quaggasrc/quagga/bgpd/bgpd.a quaggasrc/quagga/ripd/ripd.a quaggasrc/quagga/zebra/zebra.a quaggasrc/quagga/lib/libzebra.a

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '========================================================================'; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '========================================================================'; \
	echo; \
	exit 1; \
	fi