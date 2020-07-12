//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/masterServer/masterStub.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_MASTERSERVER_MASTERSTUB_H__
#define __SFLIB_MASTERSERVER_MASTERSTUB_H__

#include <SFLib/commonServer/tcpStub.h>

namespace SFLib
{
namespace Master
{
class SFLIB_MASTER_API CMasterStub : public SFLib::CommonServer::CTcpStub
{
public:
    CMasterStub(const BCLib::Network::CTcpConnectionSPtr& netConn);
    virtual ~CMasterStub();

    virtual GroupID getGroupID()
    {
        return m_groupID;
    }

protected:
    /// @brief δ�������Ϣ�ŵ� CNetMsgQueueBySFMsgLabel ������
    /// @return void
    /// @param msgLabel
    /// @param msg
    /// @param msgSize
    virtual void _unhandledMsg(SFLib::CommonServer::SSFMsgLabel& msgLabel, SFLib::Message::SNetMessage* msg, BCLib::uint32 msgSize);
    virtual bool _transformMsg(PeerID peerID, SFLib::Message::SNetMessage* msg, BCLib::uint32 msgSize);

    virtual void _cbTerminate();

    virtual bool _createMsgExecPtr(BCLib::uint16 type, BCLib::uint16 id, BCLib::Framework::CMsgExecPtr& msgExecPtr);

    virtual void _onXX2XSNtfServerType(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);
    virtual void _onXS2MSResAccept(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);
    virtual void _onMS2XSNtfServerBroken(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

    virtual void _onXS2MSNtfShakeHands(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);
    virtual void _onXS2MSNtfServerInited(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

    virtual void _onXS2MSReqEnterServer(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);
    virtual void _onXS2MSReqLeaveServer(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

    virtual void _onXS2MSReqValidRandKey(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);
    virtual void _onXS2MSAckServerSave(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

	virtual ServerID _getServerIDByType(EServerType serverType);

private:
    GroupID m_groupID;
};
}//Master
}//SFLib

#endif//__SFLIB_MASTERSERVER_MASTERSTUB_H__
