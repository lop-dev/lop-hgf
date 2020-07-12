//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/commonServer/commonServer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_COMMONSERVER_COMMONSERVER_H__
#define __SFLIB_COMMONSERVER_COMMONSERVER_H__

#include <BCLib/framework/mainThread.h>
#include <BCLib/network/tcp/tcpServer.h>
#include <SFLib/message/gameFrame.h>
#include <SFLib/commonServer/netClient/commonClient.h>
#include <SFLib/commonServer/netClient/externalClient.h>
#include <SFLib/commonServer/netClient/tcpClientMgr.h>
#include <SFLib/commonServer/netPeerMgr.h>

//#define USE_PIPESERVER_TEST_LOGIC

#include <BCLib/network/pipe/pipeServer.h>
#include <BCLib/network/pipe/pipeStubMgr.h>

namespace SFLib
{
namespace CommonServer
{

#ifndef USE_PIPESERVER_TEST_LOGIC
class SFLIB_COMMON_API CCommonServer : public BCLib::Framework::CMainThread, public BCLib::Network::CTcpServer
#else
class SFLIB_COMMON_API CCommonServer : public BCLib::Framework::CMainThread, public BCLib::Network::CPipeServer
#endif
{
public:
    CCommonServer(const std::string& name);
    virtual ~CCommonServer();

    static CCommonServer* getCommonServer()
    {
        return m_commonServer;
    }

    bool isNotifyMaster()
    {
        return m_notifyMaster;
    }

    //
    void setGroupID(GroupID groupID)
    {
        m_groupID = groupID;
    }

    virtual GroupID getGroupID()
    {
        return m_groupID;
    }

    virtual std::string getGroupName()
    {
        return "";
    }

    //
    void setServerID(ServerID serverID)
    {
        m_serverID = serverID;
    }

    ServerID getServerID()
    {
        return m_serverID;
    }

    const std::string& getServerName()
    {
        return m_serverName;
    }

    virtual EServerType getServerType() = 0;
    virtual std::string getServerVersion() = 0;

public:
    /// @brief ���������ļ�
    /// @return bool
    bool loadConfigFile(std::string configFile = "");

    /// @brief ���¼��������ļ��е�һ����ֵ
    /// @return bool
    /// @param strKey Ҫ���صļ���
    /// @param bUpdateTime �������һ�δ��ļ�ʱ����Ӧ���ļ��޸�ʱ��
    bool reloadConfigKey(std::string strKey, bool bUpdateTime = true);

    /// @brief �ж��ļ��Ƿ��Ѿ����޸Ĺ�
    /// @return bool
    bool isConfigFileModified();

    bool getReloadFlag()
    {
        return m_reloadflag;
    }
    void setReloadFlag(bool flag)
    {
        m_reloadflag = flag;
    }

public:
    /// @brief ����崻�ʱ��Ļص�,�ϲ�̳к���Ҫ���õײ�Ĵ˺���
    /// @return void
    virtual void cbProcessException();

    /// @brief ����������Ϣʧ�ܺ�Ļص�
    /// @return void
    virtual void _cbSendError(PeerID peerID, const SFLib::Message::CNetMessage* msg);

    /// @brief �ײ�ת����Ϣʧ�ܺ�Ļص�
    /// @return void
    virtual void _cbSendError(PeerID peerID, const SFLib::Message::SNetMessage* msg, BCLib::uint32 msgSize);

public:
    // ���ⲿ������������Ϣ
    bool bstMsgToExternalServer(EServerType serverType, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool bstMsgToExternalServer(EServerType serverType, const SFLib::Message::CNetMessage* msg);

    bool bstMsgToExternalServer(PeerID peerID, EServerType serverType, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool bstMsgToExternalServer(PeerID peerID, EServerType serverType, const SFLib::Message::CNetMessage* msg);

    bool sendMsgToExternalServer(ServerID serverID, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool sendMsgToExternalServer(ServerID serverID, const SFLib::Message::CNetMessage* msg);

    bool sendMsgToExternalServer(PeerID peerID, ServerID serverID, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool sendMsgToExternalServer(PeerID peerID, ServerID serverID, const SFLib::Message::CNetMessage* msg);

    // ���߼�������������Ϣ
    bool bstMsgToLogicServer(EServerType serverType, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool bstMsgToLogicServer(EServerType serverType, const SFLib::Message::CNetMessage* msg);

    bool bstMsgToLogicServer(PeerID peerID, EServerType serverType, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool bstMsgToLogicServer(PeerID peerID, EServerType serverType, const SFLib::Message::CNetMessage* msg);

    bool sendMsgToLogicServer(ServerID serverID, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool sendMsgToLogicServer(ServerID serverID, const SFLib::Message::CNetMessage* msg);

    bool sendMsgToLogicServer(PeerID peerID, ServerID serverID, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool sendMsgToLogicServer(PeerID peerID, ServerID serverID, const SFLib::Message::CNetMessage* msg);

protected:
	virtual CCommonClientPtr _cbNewLogicClient(SFLib::Message::SServerInfo& serverInfo);
	virtual CCommonClientPtr _cbNewExternalClient();

public:
    /// @brief ����Server�뱾��Server�ɹ���������
    /// @return void
    /// @param serverID �Է�ServerID
    /// @param serverType �Է�Server����
    virtual void cbServerEnter(ServerID serverID, EServerType serverType);

    /// @brief ����Server��ʼ���ɹ�
    /// @return void
    /// @param serverID �Է�ServerID
    /// @param serverType �Է�Server����
    virtual void cbServerInit(ServerID serverID, EServerType serverType);

    /// @brief ����Server�뱾��Server���ӶϿ����������쳣�Ͽ�
    /// @return void
    /// @param serverID �Է�ServerID
    /// @param serverType �Է�Server����
    virtual void cbServerLeave(ServerID serverID, EServerType serverType);

	/// @brief ����Server��Ҫ���棬��MS������֪ͨ
	/// @return void
	virtual void cbServerSave(GroupID groupID);

	/// @brief ����Server�����رգ���MS������֪ͨ
	/// @return void
	virtual void cbServerClose(GroupID groupID);

    /// @brief ����Peer�����ܱ�֤�����������Ѿ������ɹ�
    /// @return void
    /// @param netPeerPtr
    virtual void cbPeerCreate(CNetPeerPtr& netPeerPtr);

    /// @brief Peer���뱾��Server����֤�����������Ѿ������ɹ�
    /// @return void
    /// @param peerID �����PeerID
    /// @param nReason �����ԭ��
    virtual void cbPeerEnter(CNetPeerPtr& netPeerPtr, EPeerEnterReason nReason);

    /// @brief Peer�뿪����Server����֤�����������Ѿ�������Peer
    /// @return void
    /// @param peerID �뿪��PeerID
    /// @param nReason �뿪��ԭ��
    virtual void cbPeerLeave(CNetPeerPtr& netPeerPtr, EPeerLeaveReason nReason);

    /// @brief ɾ��Peer�����ܱ�֤�����������Ѿ�������Peer
    /// @return void
    /// @param netPeerPtr
    virtual void cbPeerRemove(CNetPeerPtr& netPeerPtr);

    /// @brief CNetPeer::enterXXXServer�Ļص�������֪ͨ�ò����Ƿ�ɹ�
    /// @return void
    /// @param peerID �����Peer
    /// @param ServerID ��������Server
    /// @param result �Ƿ�ɹ�
    virtual void cbPeerEnterServer(PeerID peerID, ServerID serverID, bool result);

    /// @brief CNetPeer::leaveXXXServer�Ļص�������֪ͨ�ò����Ƿ�ɹ�
    /// @return void
    /// @param peerID �����Peer
    /// @param ServerID �뿪��ǰ��Server
    /// @param result �Ƿ�ɹ�
    virtual void cbPeerLeaveServer(PeerID peerID, ServerID serverID, bool result);

    /// @brief ��Server����CNetPeer::enterXXXServer��CNetPeer::leaveXXXServer�������ı�Peer��Server������Server�����ýӿ�
    /// @return void
    /// @param peerID �����仯��Peer
    /// @param serverType �½���ķ���������
    /// @param serverID �½���ķ�������ţ���ֵ����� INVALID_SERVER_ID����ʾ�ͷ������Ͽ�����
    virtual void cbSetPeerServer(PeerID peerID, EServerType serverType, ServerID serverID);

#ifndef USE_PIPESERVER_TEST_LOGIC

public:
    void setAcceptType(BCLib::Network::ENetType acceptType)
    {
        m_acceptType = acceptType;
    }
    BCLib::Network::ENetType getAcceptType()
    {
        return m_acceptType;
    }

    void setAcceptIP(const std::string& acceptIP)
    {
        m_acceptIP = acceptIP;
    }
    const std::string& getAcceptIP()
    {
        return m_acceptIP;
    }

    void setAcceptPort(BCLib::uint16 acceptPort)
    {
        m_acceptPort = acceptPort;
    }
    BCLib::uint16 getAcceptPort()
    {
        return m_acceptPort;
    }

protected:
    virtual bool _init();
    virtual int _final();

    virtual BCLib::Network::CTcpStubMgr* _cbGetStubMgr();
    virtual bool _createMsgExecPtr(BCLib::uint16 type, BCLib::uint16 id, BCLib::Framework::CMsgExecPtr& msgExecPtr);
    virtual void _onLC2LCNtfRemoveClient(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

#else

public:
    void setAcceptType(BCLib::Network::ENetType acceptType)
    {
        m_acceptType = acceptType;
    }
    BCLib::Network::ENetType getAcceptType()
    {
        return m_acceptType;
    }

    void setAcceptIP(const std::string& acceptIP)
    {
        m_acceptIP = acceptIP;
    }
    const std::string& getAcceptIP()
    {
        return m_acceptIP;
    }

    void setAcceptPort(BCLib::uint16 acceptPort)
    {
        m_acceptPort = acceptPort;
    }
    BCLib::uint16 getAcceptPort()
    {
        return m_acceptPort;
    }

protected:
    virtual bool _init();
    virtual int _final();

    virtual BCLib::Network::CPipeStubMgr* _cbGetStubMgr();
    virtual BCLib::Network::CPipeStubSPtr _cbNewStub(const BCLib::Network::CPipeSPtr& pipePtr);
    virtual bool _createMsgExecPtr(BCLib::uint16 type, BCLib::uint16 id, BCLib::Framework::CMsgExecPtr& msgExecPtr);
    virtual void _onLC2LCNtfRemoveClient(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

#endif

public:
    CNetPeerMgr* getPeerMgr()
    {
        return m_netPeerMgr;
    }

private:
    void _setPeerMgr(CNetPeerMgr* peerMgr)
    {
        m_netPeerMgr = peerMgr;
    }

protected:
	// �Ƿ�ͨ�� Master ת������ȫ���������Ϊ true ʱ�����ֲ���ֻ�����������Ϸ�������
    bool m_notifyMaster;

private:
    static CCommonServer* m_commonServer;

    BCLib::Utility::CDateTime m_dtConfigFileLastWriteTime;
    volatile bool m_reloadflag;

    GroupID m_groupID;
    ServerID m_serverID;
    std::string m_serverName;

    BCLib::Network::ENetType m_acceptType;
    std::string m_acceptIP;
    BCLib::uint16 m_acceptPort;

    CNetPeerMgr* m_netPeerMgr;
    friend class CNetPeerMgr;
	friend class CServerMgr;
};

}//CommonServer
}//SFLib

#endif//__SFLIB_COMMONSERVER_COMMONSERVER_H__
