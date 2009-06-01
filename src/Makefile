#
# OMNeT++/OMNEST Makefile for inet-quagga
#
# This file was generated with the command:
#  opp_makemake -f --deep -I../../inetmanet/src/networklayer/arp -I../../inetmanet/src/mobility -I../../inetmanet/src/transport/sctp -I../../inetmanet/src/world -I../../inetmanet/src/transport/contract -I../../inetmanet/src/linklayer/mfcore -I../../inetmanet/src/networklayer/ted -I../../inetmanet/src/util -I../../inetmanet/src/networklayer/common -I../../inetmanet/src/networklayer/ipv6 -I../../inetmanet/src/applications/pingapp -I../../inetmanet/src/networklayer/ldp -I../../inetmanet/src/transport/tcp -I../../inetmanet/src/util/headerserializers -I../../inetmanet/src -I../../inetmanet/src/transport/udp -I../../inetmanet/src/networklayer/rsvp_te -I../../inetmanet/src/networklayer/ipv4 -I../../inetmanet/src/networklayer/icmpv6 -I../../inetmanet/src/base -I../../inetmanet/src/networklayer/contract -I../../inetmanet/src/networklayer/manetrouting/base -I../../inetmanet/src/networklayer/mpls -I../../inetmanet/src/linklayer/contract -L../../inetmanet/out/$(CONFIGNAME)/src -linet -KINETMANET_PROJ=../../inetmanet
#

# Name of target to be created (-o option)
TARGET = inet-quagga$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../inetmanet/src/networklayer/arp \
    -I../../inetmanet/src/mobility \
    -I../../inetmanet/src/transport/sctp \
    -I../../inetmanet/src/world \
    -I../../inetmanet/src/transport/contract \
    -I../../inetmanet/src/linklayer/mfcore \
    -I../../inetmanet/src/networklayer/ted \
    -I../../inetmanet/src/util \
    -I../../inetmanet/src/networklayer/common \
    -I../../inetmanet/src/networklayer/ipv6 \
    -I../../inetmanet/src/applications/pingapp \
    -I../../inetmanet/src/networklayer/ldp \
    -I../../inetmanet/src/transport/tcp \
    -I../../inetmanet/src/util/headerserializers \
    -I../../inetmanet/src \
    -I../../inetmanet/src/transport/udp \
    -I../../inetmanet/src/networklayer/rsvp_te \
    -I../../inetmanet/src/networklayer/ipv4 \
    -I../../inetmanet/src/networklayer/icmpv6 \
    -I../../inetmanet/src/base \
    -I../../inetmanet/src/networklayer/contract \
    -I../../inetmanet/src/networklayer/manetrouting/base \
    -I../../inetmanet/src/networklayer/mpls \
    -I../../inetmanet/src/linklayer/contract \
    -I. \
    -Iquaggasrc \
    -Iquaggasrc/inetport \
    -Iquaggasrc/inetport/diffs \
    -Iquaggasrc/quagga \
    -Iquaggasrc/quagga/bgpd \
    -Iquaggasrc/quagga/lib \
    -Iquaggasrc/quagga/ospfd \
    -Iquaggasrc/quagga/ripd \
    -Iquaggasrc/quagga/zebra \
    -IunitTest

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../inetmanet/out/$(CONFIGNAME)/src  -linet
LIBS += -Wl,-rpath,`abspath ../../inetmanet/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/Bgpd.o \
    $O/Daemon.o \
    $O/glue.o \
    $O/Netlink.o \
    $O/oppsim_kernel.o \
    $O/Ospfd.o \
    $O/RawSocket.o \
    $O/Ripd.o \
    $O/SocketMsg.o \
    $O/Zebra.o \
    $O/unitTest/Nothing.o \
    $O/unitTest/TestSocket.o \
    $O/unitTest/UnitTest.o \
    $O/SocketMsg_m.o

# Message files
MSGFILES = \
    SocketMsg.msg

# Other makefile variables (-K)
INETMANET_PROJ=../../inetmanet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	ln -s -f $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@mkdir -p $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f inet-quagga inet-quagga.exe libinet-quagga.so libinet-quagga.a libinet-quagga.dll libinet-quagga.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f quaggasrc/*_m.cc quaggasrc/*_m.h
	-rm -f quaggasrc/inetport/*_m.cc quaggasrc/inetport/*_m.h
	-rm -f quaggasrc/inetport/diffs/*_m.cc quaggasrc/inetport/diffs/*_m.h
	-rm -f quaggasrc/quagga/*_m.cc quaggasrc/quagga/*_m.h
	-rm -f quaggasrc/quagga/bgpd/*_m.cc quaggasrc/quagga/bgpd/*_m.h
	-rm -f quaggasrc/quagga/lib/*_m.cc quaggasrc/quagga/lib/*_m.h
	-rm -f quaggasrc/quagga/ospfd/*_m.cc quaggasrc/quagga/ospfd/*_m.h
	-rm -f quaggasrc/quagga/ripd/*_m.cc quaggasrc/quagga/ripd/*_m.h
	-rm -f quaggasrc/quagga/zebra/*_m.cc quaggasrc/quagga/zebra/*_m.h
	-rm -f unitTest/*_m.cc unitTest/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc quaggasrc/*.cc quaggasrc/inetport/*.cc quaggasrc/inetport/diffs/*.cc quaggasrc/quagga/*.cc quaggasrc/quagga/bgpd/*.cc quaggasrc/quagga/lib/*.cc quaggasrc/quagga/ospfd/*.cc quaggasrc/quagga/ripd/*.cc quaggasrc/quagga/zebra/*.cc unitTest/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Bgpd.o: Bgpd.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	Daemon.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	Bgpd.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	generic_env.h \
	oppsim_kernel.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/SocketMsg_m.o: SocketMsg_m.cc \
	SocketMsg_m.h
$O/SocketMsg.o: SocketMsg.cc \
	SocketMsg.h \
	SocketMsg_m.h
$O/glue.o: glue.cc \
	native_env.h \
	generic_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	macosx_env.h \
	zebra_env.h \
	glue.h \
	msvc_env.h
$O/Ospfd.o: Ospfd.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	Ospfd.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	Daemon.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	generic_env.h \
	oppsim_kernel.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/RawSocket.o: RawSocket.cc \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	glue.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	oppsim_kernel.h \
	generic_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	SocketMsg.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTableAccess.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	SocketMsg_m.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/Ripd.o: Ripd.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	Ripd.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	Daemon.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	generic_env.h \
	oppsim_kernel.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/Netlink.o: Netlink.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTableAccess.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	macosx_env.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	Daemon.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	oppsim_kernel.h \
	generic_env.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/Daemon.o: Daemon.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	native_env.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	Daemon.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	generic_env.h \
	oppsim_kernel.h \
	RawSocket.h \
	SocketMsg.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	SocketMsg_m.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/Zebra.o: Zebra.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	Daemon.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	Zebra.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	generic_env.h \
	oppsim_kernel.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/oppsim_kernel.o: oppsim_kernel.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPControlInfo.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTableAccess.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	macosx_env.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	Daemon.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	generic_env.h \
	oppsim_kernel.h \
	SocketMsg.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	SocketMsg_m.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/unitTest/TestSocket.o: unitTest/TestSocket.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/util/XMLUtils.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	unitTest/UnitTest.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	Daemon.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	generic_env.h \
	oppsim_kernel.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/unitTest/UnitTest.o: unitTest/UnitTest.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/util/XMLUtils.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	native_env.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	unitTest/UnitTest.h \
	Daemon.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	generic_env.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h
$O/unitTest/Nothing.o: unitTest/Nothing.cc \
	$(INETMANET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPProtocolId_m.h \
	$(INETMANET_PROJ)/src/base/NotificationBoard.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceTable.h \
	Netlink.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/RoutingTable.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPRoute.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPAddress.h \
	$(INETMANET_PROJ)/src/base/ModuleAccess.h \
	$(INETMANET_PROJ)/src/base/INotifiable.h \
	macosx_env.h \
	zebra_env.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPControlInfo_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPSocketMap.h \
	native_env.h \
	$(INETMANET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	unitTest/UnitTest.h \
	$(INETMANET_PROJ)/src/base/INETDefs.h \
	$(INETMANET_PROJ)/src/transport/contract/UDPSocket.h \
	Daemon.h \
	msvc_env.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IPDatagram_m.h \
	RawSocket.h \
	generic_env.h \
	oppsim_kernel.h \
	$(INETMANET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INETMANET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INETMANET_PROJ)/src/networklayer/ipv4/IRoutingTable.h \
	$(INETMANET_PROJ)/src/base/NotifierConsts.h \
	$(INETMANET_PROJ)/src/linklayer/contract/MACAddress.h

