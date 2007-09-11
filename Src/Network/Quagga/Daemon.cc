/*******************************************************************
*
*    This library is free software, you can redistribute it
*    and/or modify
*    it under  the terms of the GNU Lesser General Public License
*    as published by the Free Software Foundation;
*    either version 2 of the License, or any later version.
*    The library is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*    See the GNU Lesser General Public License for more details.
*
*
*********************************************************************/
#include "Daemon.h"

#include "SocketMsg.h"

#include "IPv4InterfaceData.h"

#include "UDPControlInfo_m.h"
#include "TCPCommand_m.h"
#include "IPControlInfo.h"

#define QUAGGA_UID  100
#define QUAGGA_GID  100

#include "oppsim_kernel.h"

void Daemon::init()
{
    EV << "Quagga daemon starting" << endl;

    blocked = false;
    cwd = "/";
    rootprefix = par("fsroot").stringValue();
    euid = 0; // daemon starts as root

    // stdin, stdout, stderr
    lib_descriptor_t fd_std;
    fd_std.type = FD_FILE;
    fd_std.stream = stdin;
    fd.push_back(fd_std);
    fd_std.stream = stdout;
    fd.push_back(fd_std);
    fd_std.stream = stderr;
    fd.push_back(fd_std);

    pwd_entry.pw_uid = QUAGGA_UID;
    grp_entry.gr_gid = QUAGGA_GID;

    for(int i = 0; i < 32; i++)
    {
        struct_sigaction sa;
        sa.sa_handler = SIG_DFL;
        //sigemptyset(&sa.sa_mask); XXX FIXME memset to zero?
        sa.sa_flags = 0;
        sig.push_back(sa);
    }
    
	// cached pointer used by DAEMON macro
	current_module = this;
	
    // global variable structure pointer
    varp = GlobalVars_createActiveSet();
    ASSERT(varp);
    __activeVars = varp;

   	// initialize global variables
   	GlobalVars_initializeActiveSet_lib();
}

TCPSocket* Daemon::getIfTcpSocket(int socket)
{
    ASSERT(FD_EXIST(socket));
    return (fd[socket].type == FD_TCP)? fd[socket].tcp: NULL;
}

TCPSocket* Daemon::getTcpSocket(int socket)
{
    TCPSocket *tcp = getIfTcpSocket(socket);
    ASSERT(tcp);
    return tcp;
}

UDPSocket* Daemon::getIfUdpSocket(int socket)
{
    ASSERT(FD_EXIST(socket));
    return (fd[socket].type == FD_UDP)? fd[socket].udp: NULL;
}

UDPSocket* Daemon::getUdpSocket(int socket)
{
    UDPSocket *udp = getIfUdpSocket(socket);
    ASSERT(udp);
    return udp;
}

RawSocket* Daemon::getIfRawSocket(int socket)
{
    ASSERT(FD_EXIST(socket));
    return (fd[socket].type == FD_RAW)? fd[socket].raw: NULL;
}

RawSocket* Daemon::getRawSocket(int socket)
{
    RawSocket *raw = getIfRawSocket(socket);
    ASSERT(raw);
    return raw;
}

Netlink* Daemon::getIfNetlinkSocket(int socket)
{
    ASSERT(FD_EXIST(socket));
    return (fd[socket].type == FD_NETLINK)? fd[socket].netlink: NULL;
}

Netlink* Daemon::getNetlinkSocket(int socket)
{
    Netlink *nl = getIfNetlinkSocket(socket);
    ASSERT(nl);
    return nl;
}

FILE* Daemon::getIfStream(int fildes)
{
    ASSERT(FD_EXIST(fildes));
    return (fd[fildes].type == FD_FILE)? fd[fildes].stream: NULL;
}

FILE* Daemon::getStream(int fildes)
{
    FILE *stream = getIfStream(fildes);
    ASSERT(stream);
    return stream;
}

int Daemon::getEmptySlot()
{
    // return existing if any
    for(unsigned int i = 0; i < fd.size(); i++)
    {
        if(fd[i].type != FD_EMPTY)
            continue;

        return i;
    }

    // make sure there is enough room
    ASSERT(fd.size() < FD_SETSIZE);

    // create new slot
    lib_descriptor_t newItem;
    newItem.type = FD_EMPTY;
    fd.push_back(newItem);
    return fd.size()-1;
}

int Daemon::createTcpSocket(cMessage *msg)
{
    int socket = getEmptySlot();

    ASSERT(FD_EXIST(socket));
    ASSERT(fd[socket].type == FD_EMPTY);

    TCPSocket *tcp = msg? new TCPSocket(msg): new TCPSocket();
    cGate *g = gate("tcpOut");
    ASSERT(g);
    tcp->setOutputGate(g);
    tcp->setCallbackObject(this, (void*)socket);

    lib_descriptor_t newItem;
    newItem.type = FD_TCP;
    newItem.tcp = tcp;
    newItem.blocking = true;
    newItem.error = 0;
    fd[socket] = newItem;

    EV << "created new TCP socket=" << socket <<
    	" localAddr=" << tcp->localAddress().str() << ":" << tcp->localPort() <<  
    	" remoteAddr=" << tcp->remoteAddress().str() << ":" << tcp->remotePort() << endl;

    socketMap.addSocket(tcp);

    return socket;
}

int Daemon::createUdpSocket()
{
    int socket = getEmptySlot();

    ASSERT(FD_EXIST(socket));
    ASSERT(fd[socket].type == FD_EMPTY);

    UDPSocket *udp = new UDPSocket();
    cGate *g = gate("udpOut");
    ASSERT(g);
    udp->setOutputGate(g);
    udp->setUserId(socket);
    udp->setCallbackObject(this, (void*)socket);

    lib_descriptor_t newItem;
    newItem.type = FD_UDP;
    newItem.udp = udp;
    newItem.blocking = true;
    newItem.error = 0;
    fd[socket] = newItem;

    EV << "created new UDP socket=" << socket << endl;

    return socket;
}

int Daemon::createRawSocket(int protocol)
{
    int socket = getEmptySlot();

    ASSERT(FD_EXIST(socket));
    ASSERT(fd[socket].type == FD_EMPTY);

    RawSocket *raw = new RawSocket(socket, protocol);
    cGate *g = gate("ipOut");
    ASSERT(g);
    raw->setOutputGate(g);

    lib_descriptor_t newItem;
    newItem.type = FD_RAW;
    newItem.raw = raw;
    newItem.blocking = true;
    newItem.error = 0;
    fd[socket] = newItem;

    EV << "created new UDP socket=" << socket << endl;

    return socket;
}

int Daemon::createNetlinkSocket()
{
    int socket = getEmptySlot();

    ASSERT(FD_EXIST(socket));
    ASSERT(fd[socket].type == FD_EMPTY);

    Netlink *nl = new Netlink();

    lib_descriptor_t newItem;
    newItem.type = FD_NETLINK;
    newItem.netlink = nl;
    newItem.blocking = true;
    newItem.error = 0;
    fd[socket] = newItem;

    EV << "created new Netlink socket=" << socket << endl;

    return socket;
}

int Daemon::createStream(const char *path, char *mode)
{
    int fdesc = getEmptySlot();

    ASSERT(FD_EXIST(fdesc));
    ASSERT(fd[fdesc].type == FD_EMPTY);

    lib_descriptor_t newItem;
    newItem.type = FD_FILE;
    newItem.stream = fopen(path, mode);
    newItem.blocking = true;
    newItem.error = 0;
    fd[fdesc] = newItem;

    ASSERT(newItem.stream);

    EV << "created new file descriptor=" << fdesc << " for file=" << path << endl;

    return fdesc;
}


void Daemon::sleep(simtime_t interval)
{
	EV << "blocking on sleep" << endl;
	
	setBlocked(true);
	
	waitAndEnqueue(interval, &eventQueue);
	
	setBlocked(false);
	
	current_module = DAEMON;
    __activeVars = current_module->varp;
}

bool Daemon::receiveAndHandleMessage(double timeout, const char *cmd)
{
    cMessage *msg;
    
	if(eventQueue.empty())
	{
		EV << "blocking on syscall=" << cmd << endl;
	
    	setBlocked(true);
    
    	if(timeout == 0.0) msg = receive();
    	else msg = receive(timeout);
    
    	setBlocked(false);
    
    	current_module = DAEMON;
    	__activeVars = current_module->varp;
	}
	else
	{
		EV << "consuming queued message on syscall=" << cmd << endl;
		
		msg = (cMessage*)eventQueue.pop();
	}
    
    if(msg)
    {
        handleReceivedMessage(msg);
        return true;
    }
    else
    {
        return false;
    }
}

bool Daemon::hasQueuedConnections(int socket)
{
   ASSERT(FD_EXIST(socket));
   ASSERT(fd[socket].type == FD_TCP);

   return !fd[socket].incomingQueue.empty();
}
    
int Daemon::connectTcpSocket(int socket, IPAddress destAddr, int destPort)
{
    EV << "connect socket=" << socket << " to " << destAddr << ":" << destPort << endl;

    TCPSocket *tcp = getTcpSocket(socket);
    
    tcp->connect(destAddr, destPort);

    if(isBlocking(socket))
    {
        while(true)
        {
            receiveAndHandleMessage(0.0, "connect");
            
            if(tcp->state() == tcp->CONNECTED)
                break;
        } 
        
        EV << "connection fully established" << endl;
        
        return 0;
    }
    else
    {
    	EV << "connection in progress" << endl;
    	
    	*GlobalVars_errno() = EINPROGRESS;
	    return -1;
    }
}    

int Daemon::acceptTcpSocket(int socket)
{
    ASSERT(FD_EXIST(socket));
    ASSERT(fd[socket].type == FD_TCP);
    
    while(fd[socket].blocking && fd[socket].incomingQueue.empty())
    {
        receiveAndHandleMessage(0.0, "accept");
    }
    
    if(fd[socket].incomingQueue.empty())
    {
    	*GlobalVars_errno() = EAGAIN;
        return -1;
    }
            
    EV << "ready to accept connection" << endl;            

    int ret = fd[socket].incomingQueue.front();

    fd[socket].incomingQueue.pop_front();

    return ret;
}

bool Daemon::isBlocking(int fildes)
{
    ASSERT(fildes >= 0 && fildes < fd.size());
    
    return fd[fildes].blocking;
}

void Daemon::setBlocking(int fildes, bool blocking)
{
	ASSERT(fildes >= 0 && fildes < fd.size());
	
	EV << "marking descriptor " << fildes << " as " << (blocking?"blocking":"non-blocking") << endl;
	
	fd[fildes].blocking = blocking;
}

int Daemon::getSocketError(int fildes, bool clear) 
{
	ASSERT(fildes >= 0 && fildes < fd.size());
	ASSERT(fd[fildes].type == FD_TCP || fd[fildes].type == FD_UDP);
	
	int ret = fd[fildes].error;
	if(clear) fd[fildes].error = 0;
	return ret; 
}	

void Daemon::handleReceivedMessage(cMessage *msg)
{
    UDPControlInfo *udpControlInfo = dynamic_cast<UDPControlInfo*>(msg->controlInfo());
    TCPCommand *tcpCommand = dynamic_cast<TCPCommand*>(msg->controlInfo());
    IPControlInfo *ipControlInfo = dynamic_cast<IPControlInfo*>(msg->controlInfo());
    
    int socket;

    if(udpControlInfo)
    {
        // UDP packet
        
        socket = udpControlInfo->userId();
        
		getUdpSocket(socket)->processMessage(msg);

    }
    else if(tcpCommand)
    {
        // TCP packet
        
        socket = findTcpSocket(msg);
        
        if(socket >= 0)
        {
            // known socket, incomming data
        	
            getTcpSocket(socket)->processMessage(msg);
        }
        else if(msg->kind() == TCP_I_ESTABLISHED)        
        {
            // create new socket
            int csocket = createTcpSocket(msg);
            
            // find parent socket
            socket = findServerSocket(check_and_cast<TCPConnectInfo*>(tcpCommand));
            
            // put in the list for accept
            enqueueConnection(socket, csocket);
        }
        else
        {
        	EV << "throwing message away (socket doesn't exist)" << endl; 
        	delete msg;
        }
    }
    else if(ipControlInfo)
    {
        // IP Packet

        ASSERT(!strcmp(msg->name(), "data"));

        socket = findRawSocket(ipControlInfo->protocol());

        if(socket < 0)
        {
            EV << "no recipient (socket) for this message, discarding" << endl;

            delete msg;
            return;
        }

        enqueueSocketMessage(socket, msg);
    }
    else
        ASSERT(false);
}

void Daemon::enqueueConnection(int socket, int csocket)
{
    ASSERT(getIfTcpSocket(socket));
    ASSERT(getIfTcpSocket(csocket));
    ASSERT(socket < csocket);
    fd[socket].incomingQueue.push_back(csocket);
}

cMessage* Daemon::getSocketMessage(int socket, bool remove)
{
    ASSERT(FD_EXIST(socket));

    if(fd[socket].queue.empty())
        return NULL;

    cMessage *msg = (cMessage*)fd[socket].queue.front();

    if(remove)
        fd[socket].queue.remove(msg);

    return msg;
}

void Daemon::enqueueSocketMessage(int socket, cMessage *msg)
{
    ASSERT(FD_EXIST(socket));

    fd[socket].queue.insert(msg);
}

void Daemon::closeSocket(int socket)
{
	// NOTE: close returns immediately, currently there is no support for SO_LINGER
	
    ASSERT(FD_EXIST(socket));
    
    switch(fd[socket].type)
    {
        case FD_UDP:
            ASSERT(fd[socket].udp);
            fd[socket].udp->close();
            delete fd[socket].udp;
            fd[socket].udp = NULL;
            break;
            
        case FD_TCP:
            ASSERT(fd[socket].tcp);
            fd[socket].tcp->close();
            socketMap.removeSocket(fd[socket].tcp);
            delete fd[socket].tcp;
            fd[socket].tcp = NULL;
            break;
            
        default:
            // closing raw or netlink socket currently not implemented/used
            ASSERT(false);
    }
            
    fd[socket].type = FD_EMPTY;
}

void Daemon::closeStream(int fildes)
{
    ASSERT(FD_EXIST(fildes));
    ASSERT(fd[fildes].type == FD_FILE);
    ASSERT(fd[fildes].stream);

    fclose(fd[fildes].stream);
    fd[fildes].stream = NULL;
    fd[fildes].type = FD_EMPTY;
}

int Daemon::findTcpSocket(cMessage *msg)
{
    ASSERT(TCPSocket::belongsToAnyTCPSocket(msg));

    TCPSocket *socket = socketMap.findSocketFor(msg);
    if(!socket)
    {
        EV << "connection not found" << endl;
        return -1;
    }

    ASSERT(socket);

    for(int i = 0; i < fd.size(); i++)
    {
        if(fd[i].type != FD_TCP)
            continue;

        if(fd[i].tcp != socket)
            continue;

        return i;
    }

    ASSERT(false);
}

int Daemon::findRawSocket(int protocol)
{
    for(int i = 0; i < fd.size(); i++)
    {
        if(fd[i].type != FD_RAW)
            continue;

        if(fd[i].raw->getProtocol() != protocol)
            continue;

        return i;
    }

    return -1;
}

int Daemon::findServerSocket(TCPConnectInfo *info)
{
	// this is not efficient, but shoulf always give valid result (right?)

    int port = info->localPort();
    IPAddress addr = info->localAddr().get4();
    
    for(unsigned int i = 0; i < fd.size(); i++)
    {
        if(fd[i].type != FD_TCP)
            continue;

        if(fd[i].tcp->localPort() != port)
            continue;

        if(!fd[i].tcp->localAddress().equals(addr) && !fd[i].tcp->localAddress().isUnspecified())
            continue;

        return i;
    }

    return -1;
}

std::string Daemon::getcwd()
{
    return cwd;
}

std::string Daemon::getrootprefix()
{
    return rootprefix;
}

struct_sigaction * Daemon::sigactionimpl(int signo)
{
    ASSERT(signo >= 0);
    ASSERT(signo < sig.size());
    return &sig[signo];
}

void Daemon::setBlocked(bool b)
{
    ASSERT(blocked != b);
    
    if(b) EV << "blocking" << endl;
    else EV << "unblocking" << endl;

    blocked = b;
}

void Daemon::socketDataArrived(int connId, void *yourPtr, cMessage *msg, bool urgent)
{
    int socket = (long)yourPtr;

    EV << "data arrived on socket=" << socket << endl;

    enqueueSocketMessage(socket, msg);
}

void Daemon::socketEstablished(int connId, void *yourPtr)
{
    int socket = (long)yourPtr;
    
    EV << "socket=" << socket << " established" << endl;
}

void Daemon::socketFailure(int connId, void *yourPtr, int code)
{
	int socket = (long)yourPtr;	
	
	EV << "failure on socket=" << socket << " code=" << code << endl;
	
	ASSERT(FD_EXIST(socket) && fd[socket].type == FD_TCP);
	ASSERT(code != 0);
	
	fd[socket].error = code;
}

void Daemon::socketDatagramArrived(int sockId, void *yourPtr, cMessage *msg, UDPControlInfo *ctrl)
{
	int socket = (long)yourPtr;	
	
	ASSERT(FD_EXIST(socket) && fd[socket].type == FD_UDP);
	
	// we will need the source address later in recvfrom syscall
	msg->setControlInfo(ctrl);
	
	enqueueSocketMessage(socket, msg);
}

void Daemon::socketPeerClosed(int sockId, void *yourPtr)
{
	int socket = (long)yourPtr;	
	
	ASSERT(FD_EXIST(socket));
	
	fd[socket].error = -1; // XXX FIXME (???)
	
	if(fd[socket].type == FD_TCP) {
		socketMap.removeSocket(fd[socket].tcp);
	}
}
