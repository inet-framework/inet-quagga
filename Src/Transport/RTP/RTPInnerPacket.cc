/***************************************************************************
                          RTPInnerPacket.cc  -  description
                             -------------------
    begin                : Sat Oct 20 2001
    copyright            : (C) 2001 by Matthias Oppitz
    email                : Matthias.Oppitz@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


/** \file RTPInnerPacket.cc
 * This file contains the implementation of member functions
 * of RTPInnerPacket.
 */

#include <omnetpp.h>

#include "RTPInnerPacket.h"
#include "RTPPacket.h"

Register_Class(RTPInnerPacket);


RTPInnerPacket::RTPInnerPacket(const char *name) : cPacket(name) {
    _type = RTP_INP_UNDEF;
    _commonName = NULL;
    _mtu = 0;
    _bandwidth = 0;
    _rtcpPercentage = 0;
    _address = IPADDRESS_UNDEF;
    _port = IPSuite_PORT_UNDEF;
    _ssrc = 0;
    _payloadType = 0;
    _fileName = NULL;
    _clockRate = 0;
    _timeStampBase = 0;
    _sequenceNumberBase = 0;
};


RTPInnerPacket::RTPInnerPacket(const RTPInnerPacket& rinp) : cPacket() {
    setName(rinp.name());
    operator=(rinp);
};


RTPInnerPacket::~RTPInnerPacket() {
    if (opp_strcmp(_commonName, ""))
        delete _commonName;
    if (opp_strcmp(_fileName, ""))
        delete _fileName;
};


RTPInnerPacket& RTPInnerPacket::operator=(const RTPInnerPacket& rinp) {
    cPacket::operator=(rinp);
    _type = rinp._type;
    _commonName = opp_strdup(rinp._commonName);
    _mtu = rinp._mtu;
    _bandwidth = rinp._bandwidth;
    _rtcpPercentage = rinp._rtcpPercentage;
    _address = rinp._address;
    _port = rinp._port;
    _ssrc = rinp._ssrc;
    _payloadType = rinp._payloadType;
    _fileName = opp_strdup(rinp._fileName);
    _clockRate = rinp._clockRate;
    _timeStampBase = rinp._timeStampBase;
    _sequenceNumberBase = rinp._sequenceNumberBase;
    return *this;
};


cObject *RTPInnerPacket::dup() const {
    return new RTPInnerPacket(*this);
};


const char *RTPInnerPacket::className() const {
    return "RTPInnerPacket";
};


std::string RTPInnerPacket::info() {
    std::stringstream out;
    out << "RTPInnerPacket: type=" << _type;
    return out.str();
};


void RTPInnerPacket::writeContents(std::ostream& os) const {
    os << "RTPInnerPacket:" << endl;
    os << "  type = " << _type << endl;
    os << "  commonName = " << _commonName << endl;
    os << "  mtu = " << _mtu << endl;
    os << "  bandwidth = " << _bandwidth << endl;
    os << "  rtcpPercentage = " << _rtcpPercentage << endl;
    os << "  address = " << _address << endl;
    os << "  port = " << _port << endl;
    os << "  ssrc = " << _ssrc << endl;
    os << "  payloadType = " << _payloadType << endl;
    os << "  fileName = " << _fileName << endl;
    os << "  clockRate = " << _clockRate << endl;
    os << "  timeStampBase = " << _timeStampBase << endl;
    os << "  sequenceNumberBase = " << _sequenceNumberBase << endl;
};


void RTPInnerPacket::initializeProfile(int mtu) {
    _type = RTP_INP_INITIALIZE_PROFILE;
    _mtu = mtu;
};


void RTPInnerPacket::profileInitialized(int rtcpPercentage, IN_Port port) {
    _type = RTP_INP_PROFILE_INITIALIZED;
    _rtcpPercentage = rtcpPercentage;
    _port = port;
};


void RTPInnerPacket::initializeRTCP(const char *commonName, int mtu, int bandwidth, int rtcpPercentage, IN_Addr address, IN_Port port) {
    _type = RTP_INP_INITIALIZE_RTCP;
    _commonName = commonName;
    _mtu = mtu;
    _bandwidth = bandwidth;
    _rtcpPercentage = rtcpPercentage;
    _address = address;
    _port = port;
};


void RTPInnerPacket::rtcpInitialized(u_int32 ssrc) {
    _type = RTP_INP_RTCP_INITIALIZED;
    _ssrc = ssrc;
};


void RTPInnerPacket::createSenderModule(u_int32 ssrc, int payloadType, const char *fileName) {
    _type = RTP_INP_CREATE_SENDER_MODULE;
    _ssrc = ssrc;
    _payloadType = payloadType;
    _fileName = fileName;
};


void RTPInnerPacket::senderModuleCreated(u_int32 ssrc) {
    _type = RTP_INP_SENDER_MODULE_CREATED;
    _ssrc = ssrc;
};


void RTPInnerPacket::deleteSenderModule(u_int32 ssrc) {
    _type = RTP_INP_DELETE_SENDER_MODULE;
    _ssrc = ssrc;
};


void RTPInnerPacket::senderModuleDeleted(u_int32 ssrc) {
    _type = RTP_INP_SENDER_MODULE_DELETED;
    _ssrc = ssrc;
};


void RTPInnerPacket::initializeSenderModule(u_int32 ssrc, const char *fileName, int mtu) {
    _type = RTP_INP_INITIALIZE_SENDER_MODULE;
    _ssrc = ssrc;
    _fileName = fileName;
    _mtu = mtu;
};


void RTPInnerPacket::senderModuleInitialized(u_int32 ssrc, int payloadType, int clockRate, int timeStampBase, int sequenceNumberBase) {
    _type = RTP_INP_SENDER_MODULE_INITIALIZED;
    _ssrc = ssrc;
    _payloadType = payloadType;
    _clockRate = clockRate;
    _timeStampBase = timeStampBase;
    _sequenceNumberBase = sequenceNumberBase;
};

void RTPInnerPacket::senderModuleControl(u_int32 ssrc, RTPSenderControlMessage *msg) {
    _type = RTP_INP_SENDER_MODULE_CONTROL;
    _ssrc = ssrc;
    encapsulate(msg);
};


void RTPInnerPacket::senderModuleStatus(u_int32 ssrc, RTPSenderStatusMessage *msg) {
    _type = RTP_INP_SENDER_MODULE_STATUS;
    _ssrc = ssrc;
    encapsulate(msg);
};


void RTPInnerPacket::leaveSession() {
    _type = RTP_INP_LEAVE_SESSION;
};


void RTPInnerPacket::sessionLeft() {
    _type = RTP_INP_SESSION_LEFT;
};


void RTPInnerPacket::dataOut(RTPPacket *packet) {
    _type = RTP_INP_DATA_OUT;
    encapsulate(packet);
};


void RTPInnerPacket::dataIn(RTPPacket *packet, IN_Addr address, IN_Port port) {
    _type = RTP_INP_DATA_IN;
    _address = address;
    _port = port;
    encapsulate(packet);
};


RTPInnerPacket::RTP_INP_TYPE RTPInnerPacket::type() {
    return _type;
};


const char *RTPInnerPacket::commonName() {
    return opp_strdup(_commonName);
};


int RTPInnerPacket::mtu() {
    return _mtu;
};


int RTPInnerPacket::bandwidth() {
    return _bandwidth;
};


int RTPInnerPacket::rtcpPercentage() {
    return _rtcpPercentage;
};


IN_Addr RTPInnerPacket::address() {
    return _address;
};


IN_Port RTPInnerPacket::port() {
    return _port;
};


u_int32 RTPInnerPacket::ssrc() {
    return _ssrc;
};


const char *RTPInnerPacket::fileName() {
    return opp_strdup(_fileName);
};


int RTPInnerPacket::payloadType() {
    return _payloadType;
};


int RTPInnerPacket::clockRate() {
    return _clockRate;
};


int RTPInnerPacket::timeStampBase() {
    return _timeStampBase;
};


int RTPInnerPacket::sequenceNumberBase() {
    return _sequenceNumberBase;
};
