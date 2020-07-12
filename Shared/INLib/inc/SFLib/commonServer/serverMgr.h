//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/commonServer/serverMgr.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_COMMONSERVER_SERVERMGR_H__
#define __SFLIB_COMMONSERVER_SERVERMGR_H__

#include <vector>
#include <BCLib/utility/hashMap.h>
#include <BCLib/utility/singleton.h>
#include <SFLib/message/gameFrame.h>
#include <SFLib/message/message.h>
#include <SFLib/commonServer/msgLabel.h>
#include <BCLib/network/tcp/tcpSend.h>
#include <SFLib/commonServer/xmlConfig.h>
#include <SFLib/commonServer/netClient/externalClient.h>

namespace SFLib
{
namespace CommonServer
{

enum EServerState
{
    ESERVERSTATE_NORMAL,        // ����״̬
    ESERVERSTATE_RESTART,       // ׼������
};

class SFLIB_COMMON_API CServerMgr
{
    BCLIB_SINGLETON_DECLARE(CServerMgr);

public:
    CServerMgr();
    virtual ~CServerMgr();

    void setLogicServerList(const SFLib::Message::SMsgMS2XSNtfLogicServerList* msg, int msgSize);
    void setExternalServerList(const SFLib::Message::SMsgMS2XSNtfExternalServerList* msg, int msgSize);

    bool getServerInfo(ServerID serverID, SFLib::Message::SServerInfo& serverInfo);

    std::vector<SFLib::Message::SServerInfo> getLogicServerList();
    std::vector<SFLib::Message::SServerInfo> getExternalServerList();

	std::vector<SFLib::Message::SServerInfo> getServerList();
	std::vector<SFLib::Message::SServerInfo> getServerList(bool bConnected);

    void setNetSendByClient(ServerID serverID);
    void setNetSendByStub(ServerID serverID);
    bool isSetNetSend(ServerID serverID);
    bool isConnectionValid(ServerID serverID);

	void dumpInfo();
    bool ntfNetworkInfo2MS(BCLib::uint16 uCount);

    //
    int getLogicServerIDs(BCLib::uint64 groupID, EServerType serverType, std::vector<ServerID>& vecServerID, bool bActive = false);
    SFLib::ServerID randomLogicServerID(BCLib::uint64 groupID, ServerType serverType, bool bActive = false);

    int getExternalServerIDs(EServerType serverType, std::vector<ServerID>& vecServerID, bool bActive = false);
    SFLib::ServerID randomExternalServerID(ServerType serverType, bool bActive = false);

    int getGatewayServerIDs(EServerType serverType, std::vector<ServerID>& vecServerID, bool bActive = false);
    SFLib::ServerID randomGatewayServerID(EServerType serverType, bool bActive = false);

public:
	bool connectExternalServer(SFLib::ServerID serverID);
	bool connectExternalServers(SFLib::ServerType serverType = INVALID_SERVER_TYPE);

public:
    virtual bool bstMsgToXSByType(EServerType serverType, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    virtual bool bstMsgToXSByType(EServerType serverType, const SFLib::Message::CNetMessage* msg);

    virtual bool bstMsgToXSByType(PeerID peerID, EServerType serverType, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    virtual bool bstMsgToXSByType(PeerID peerID, EServerType serverType, const SFLib::Message::CNetMessage* msg);

    virtual bool sendMsgToXSByID(ServerID serverID, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    virtual bool sendMsgToXSByID(ServerID serverID, const SFLib::Message::CNetMessage* msg);

    virtual bool sendMsgToXSByID(PeerID peerID, ServerID serverID, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    virtual bool sendMsgToXSByID(PeerID peerID, ServerID serverID, const SFLib::Message::CNetMessage* msg);

protected:
    // ����ӿ��Ǹ� CXmlConfig ר�õģ�Ҳ���Ǹ� MasterServer ר�õ�
    void _sendServerListToStubs();

private:
    void _clear();

private:
    struct SServerInfoExt
    {
		SServerInfoExt()
        {
			m_netSend = NULL;
			m_bStub = false;
            m_eServerState = ESERVERSTATE_NORMAL;
        }

        int send(const SFLib::Message::CNetMessage* msg);
        int send(const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);

		SFLib::CommonServer::SServerInfo m_serverInfo;
        BCLib::Network::CTcpSendSPtr m_netSend;
		bool m_bStub;
        EServerState m_eServerState;
    };
    bool _isConnected(SServerInfoExt* pServerInfoExt);

private:
    BCLib::Utility::CMutex m_mutexServerList;
    BCLib::Utility::CHashMap<BCLib::uint32, SServerInfoExt*> m_serverListByID;
    std::vector<SServerInfoExt*> m_serverListByType[ESERVER_MAX - ESERVER_GAMECLIENT];

    friend class CXmlConfig;
};

}//CommonServer
}//SFLib

#endif//__SFLIB_COMMONSERVER_SERVERMGR_H__
