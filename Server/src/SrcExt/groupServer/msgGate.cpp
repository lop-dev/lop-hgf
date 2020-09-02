//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   groupServer/msgGate.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#include "msgGate.h"
#include <MSLib/commonDefine/message.h>
#include <PBLib/protobuf/message.pb.h>
#include <SHLib/commonDefine/logFile.h>
#include <SFLib/externalServer/netPeerMgr.h>

namespace LOP
{

    BCLIB_SINGLETON_DEFINE(CMsgGate);

    CMsgGate::CMsgGate()
    {
    }

    CMsgGate::~CMsgGate()
    {
    }

    void CMsgGate::init()
    {
        static bool bInit = false;
        if (!bInit)
        {
            bInit = true;
        }
    }

    void CMsgGate::update()
    {
        SFLib::CommonServer::CNetMsgQueueBySFMsgLabel::singleton().doParse(*this);
    }

    bool CMsgGate::parse(const SFLib::CommonServer::SSFMsgLabel& msgLabel, const SFLib::Message::SNetMessage* netMessage, const BCLib::uint32 netMessageSize)
    {
        BCLIB_LOG_DEBUG(SHLib::ELOGMODULE_SHLIB_DEFAULT, "CNetMsgGate::parse：处理消息Peer[%llu]：消息详情[%s]", msgLabel.m_peerID, netMessage->getDebugPrompt().c_str());
        if (netMessage->getServer() == SFLib::ESERVER_LOCAL && netMessage->getFunc() == PBLib::EFUNC_SFCBSYSTEM && netMessage->getID() == MSLib::EMID_LC2LC_SFCALLBACK)
        {
            _onSFCallback(netMessage);
            return true;
        }
        return this->parseMsg(msgLabel, netMessage, netMessageSize);
    }

    void CMsgGate::_onSFCallback(const SFLib::Message::SNetMessage* msg)
    {
        const MSLib::SMsgLC2LCSFCallback* msgCallback = static_cast<const MSLib::SMsgLC2LCSFCallback*>(msg);

        switch (msgCallback->m_cbType)
        {
        case MSLib::SMsgLC2LCSFCallback::ESCT_SERVER_INIT:
            break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_SERVER_ENTER:
            break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_SERVER_LEAVE:
            break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_SERVER_CLOSE:
            break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_PEER_ENTER:
            break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_PEER_LEAVE:
            break;
        default:
            break;
        }
    }

}//namespace LOP
