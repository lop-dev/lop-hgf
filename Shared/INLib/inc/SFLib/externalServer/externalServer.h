//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/externalServer/externalServer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_EXTERNALSERVER_EXTERNALSERVER_H__
#define __SFLIB_EXTERNALSERVER_EXTERNALSERVER_H__

#include <SFLib/commonServer/commonServer2Master.h>
#include <BCLib/network/udp/udpServer.h>
#include <SFLib/externalServer/netPeer.h>

namespace SFLib
{
namespace External
{
class SFLIB_EXTERNAL_API CExternalServer : public SFLib::CommonServer::CCommonServer2Master
{
public:
    CExternalServer(const std::string& name);
    virtual ~CExternalServer();

protected:
    virtual bool _init();

    virtual BCLib::Network::CTcpStubSPtr _cbNewStub(const BCLib::Network::CTcpConnectionSPtr& connPtr);

	virtual SFLib::CommonServer::CTcpClientPtr _cbNewMasterClient();
    virtual CNetPeerPtr _cbNewPeer(PeerID peerID, ServerID gatewayServerID, BCLib::Network::TcpStubID gameClientStubID);

private:
    BCLib::Network::CUdpServer m_udpSrv;

    friend class CMasterClient;
    friend class CExternalClient;
    friend class CExternalStub;
    friend class CNetPeerMgr;
};
}//External
}//SFLib

#endif//__SFLIB_EXTERNALSERVER_EXTERNALSERVER_H__
