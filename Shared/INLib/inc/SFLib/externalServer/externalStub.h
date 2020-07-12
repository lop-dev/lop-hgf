//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/externalServer/externalStub.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_EXTERNALSERVER_EXTERNALSTUB_H__
#define __SFLIB_EXTERNALSERVER_EXTERNALSTUB_H__

#include <SFLib/commonServer/tcpStub.h>
#include <SFLib/commonServer/netClient/tcpClient.h>
#include <SFLib/message/peerMsg.h>

namespace SFLib
{
namespace External
{
class SFLIB_EXTERNAL_API CExternalStub : public SFLib::CommonServer::CTcpStub
{
public:
    CExternalStub(const BCLib::Network::CTcpConnectionSPtr& netConn);
    virtual ~CExternalStub();

protected:
    /// @brief δ�������Ϣ�ŵ� CNetMsgQueueByGroupKey ������
    /// @return void
    /// @param msgLabel
    /// @param msg
    /// @param msgSize
    virtual void _unhandledMsg(SFLib::CommonServer::SSFMsgLabel& msgLabel, SFLib::Message::SNetMessage* msg, BCLib::uint32 msgSize);
    //virtual bool _transformMsg(PeerID peerID, SFLib::Message::SNetMessage* msg, BCLib::uint32 msgSize);

    virtual void _cbTerminate();
    virtual bool _createMsgExecPtr(BCLib::uint16 type, BCLib::uint16 id, BCLib::Framework::CMsgExecPtr& msgExecPtr);

    virtual void _onXX2XSNtfServerType(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

	virtual void _onXS2XSReqEnterServer(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);
	virtual void _onXS2XSReqLeaveServer(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

    virtual void _onXS2XSReqEnterOrLeaveServer(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

private:
    void _doReqEnterServer(SFLib::Message::SReqEnterOrLeaveServer& reqEnterOrLeaveServer, SFLib::Message::SResEnterOrLeaveServer& resEnterOrLeaveServer);
    void _doReqLeaveServer(SFLib::Message::SReqEnterOrLeaveServer& reqEnterOrLeaveServer, SFLib::Message::SResEnterOrLeaveServer& resEnterOrLeaveServer);
};
typedef BCLib::Utility::CSPointer<CExternalStub> CExternalStubPtr;
}//External
}//SFLib

#endif//__SFLIB_EXTERNALSERVER_EXTERNALSTUB_H__
