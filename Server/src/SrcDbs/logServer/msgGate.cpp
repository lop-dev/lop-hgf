//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   logServer/msgGate.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#include "msgGate.h"
#include <SFLib/logicServer/netPeerMgr.h>
#include <STLib/commonDefine/logFile.h>
#include <MSLib/commonDefine/message.h>
#include <SHLib/commonDefine/baseDef.h>

#include "logServer.h"
#include "logApp.h"

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
            //addMsgExecMgr(PBLib::EFUNC_LOGSYSTEM, &CLogSystem::singleton());
            //addMsgExecMgr(PBLib::EFUNC_COMMANDSYSTEM, &CCommandSystem::singleton());
            bInit = true;
        }
    }

    void CMsgGate::update()
    {
        SFLib::CommonServer::CNetMsgQueueBySFMsgLabel::singleton().doParse(*this);
    }

    bool CMsgGate::parse(const SFLib::CommonServer::SSFMsgLabel& msgLabel, const SFLib::Message::SNetMessage* netMessage, const BCLib::uint32 netMessageSize)
    {
        BCLIB_LOG_DEBUG(STLib::ELOGMODULE_STLIB_DEFAULT, "CNetMsgGate::parse：处理消息Peer[%llu]：消息详情[%s]", msgLabel.m_peerID, netMessage->getDebugPrompt().c_str());

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
        case MSLib::SMsgLC2LCSFCallback::ESCT_SERVER_SAVE:
        {
            // TODO : 做完保存后，需要给 MS 回复一下，目前只针对 LogicServer 而言
            SFLib::CommonServer::CMasterClientPtr masterClient = SFLib::CommonServer::CCommonServer2Master::getCommonServer2Master()->getMasterClient();
            if (masterClient != NULL)
            {
                BCLIB_LOG_INFOR(STLib::ELOGMODULE_STLIB_DEFAULT, "CNetMsgGate::_onSFCallback : ESCT_SERVER_SAVE : ackServerSave");
                masterClient->ackServerSave(0);
            }
        }
        break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_SERVER_CLOSE:
        {
            CLogApp::singleton().setClosing(true);
        }
        break;
        //
        case MSLib::SMsgLC2LCSFCallback::ESCT_PEER_CREATE:
            BCLIB_LOG_INFOR(STLib::ELOGMODULE_STLIB_DEFAULT, "CNetMsgGate::_onSFCallback : ESCT_PEER_CREATE : PeerID<%llu>", msgCallback->m_peerID);
            break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_PEER_ENTER:
        {
            BCLIB_LOG_INFOR(STLib::ELOGMODULE_STLIB_DEFAULT, "CNetMsgGate::_onSFCallback : ESCT_PEER_ENTER : PeerID<%llu>", msgCallback->m_peerID);
        }
        break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_PEER_LEAVE:
        {
            BCLIB_LOG_INFOR(STLib::ELOGMODULE_STLIB_DEFAULT, "CNetMsgGate::_onSFCallback : ESCT_PEER_LEAVE : PeerID<%llu>", msgCallback->m_peerID);
            SFLib::Logic::CNetPeerPtr netPeer = SFLib::Logic::CNetPeerMgr::singleton().getNetPeer(msgCallback->m_peerID);
            if (netPeer == NULL)
            {
                BCLIB_LOG_ERROR(STLib::ELOGMODULE_STLIB_DEFAULT, "peerID[%llu] not found netPeer!!", msgCallback->m_peerID);
                return;
            }

            netPeer->ackLeave();
        }
        break;
        case MSLib::SMsgLC2LCSFCallback::ESCT_PEER_REMOVE:
            BCLIB_LOG_INFOR(STLib::ELOGMODULE_STLIB_DEFAULT, "CNetMsgGate::_onSFCallback : ESCT_PEER_REMOVE : PeerID<%llu>", msgCallback->m_peerID);
            break;
        default:
            break;
        }
    }

}//namespace LOP
