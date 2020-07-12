//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/logicServer/netPeer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_LOGICSERVER_NETPEER_H__
#define __SFLIB_LOGICSERVER_NETPEER_H__

#include <SFLib/commonServer/netPeer.h>
#include <SFLib/commonServer/tcpStub.h>
#include <SFLib/commonServer/netClient/masterClient.h>
#include <SFLib/message/peerMsg.h>

namespace SFLib
{
namespace Logic
{
class SFLIB_LOGIC_API CNetPeer : public SFLib::CommonServer::CNetPeer
{
public:
    CNetPeer();
    CNetPeer(PeerID peerID, ServerID gatewayServerID, BCLib::Network::TcpStubID gameClientStubID);
    virtual ~CNetPeer();

    /// @brief �����뿪
    /// @return bool
    /// @param nReason : 1 ����������ң�2 �����¼����
    virtual bool reqLeave(EPeerLeaveReason nReason);

    /// @brief �����뿪
    /// @return void
    virtual void ackLeave();

    virtual void terminate();

	virtual bool serializeTo(BCLib::Utility::CStream& stream) const;
	virtual bool serializeFrom(BCLib::Utility::CStream& stream);

public:
	virtual ServerID getServerID(EServerType serverType);
    virtual EServerType getServerType(ServerID serverID);

	/// @brief ������Ϣ������������
	/// @return bool
	/// @param serverType ����������
	///        ���ʹ�� enterLogicServer(ServerID serverID) ��������Ļ�����ֱ�ӷ�����Ϣ�����������
	///        ���ʹ�� enterLogicServer(EServerType serverType) ��������Ļ��������һ�����������з���
    virtual bool sendMsgByType(ServerType serverType, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
	virtual bool sendMsgByType(ServerType serverType, const SFLib::Message::CNetMessage* msg);

    virtual bool sendMsgToGC(const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
	virtual bool sendMsgToGC(const SFLib::Message::CNetMessage* msg);

	bool sendMsgToMS(const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);
    bool sendMsgToMS(const SFLib::Message::CNetMessage* msg);

public:
	virtual BCLib::uint32 getLogicServerNum();

public:
	ServerID getGatewayServerID() { return m_gatewayServerID; }
    void setGatewayServerID(ServerID gatewayServerID) { m_gatewayServerID = gatewayServerID; }

	BCLib::Network::TcpStubID getGameClientStubID() { return m_gameClientStubID; }
    void setGameClientStubID(BCLib::Network::TcpStubID gameClientStubID);

	SFLib::CommonServer::CTcpStubPtr getGameClientStub() { return m_gameClientStub;	}

	BCLib::uint32 getPingValue();

public:
    /// @brief �������ĳ���߼�������
    /// @return bool
    /// @param serverID ������ID
    bool enterLogicServer(ServerID serverID, EPeerEnterReason nReason);

    /// @brief �����뿪ĳ���߼�������
    /// @return bool
	/// @param serverID ������ID
    bool leaveLogicServer(ServerID serverID, EPeerLeaveReason nReason);

	/// @brief �������ĳ���ⲿ������
	/// @return bool
	/// @param serverID ������ID
	bool enterExternalServer(ServerID serverID);

	/// @brief �������ĳ���ⲿ������
	/// @return bool
	/// @param serverID ������ID
	bool leaveExternalServer(ServerID serverID, EPeerLeaveReason nReason);

	/// @brief �������ĳ���ⲿ������
	/// @return bool
	/// @param serverType ����������
	bool enterExternalServer(EServerType serverType);

	/// @brief �����뿪ĳ���ⲿ������
	/// @return bool
	/// @param serverType ����������
	bool leaveExternalServer(EServerType serverType, EPeerLeaveReason nReason);

protected:
    virtual void _setLogicServerInfo(EServerType serverType, ServerID serverID);
    virtual void _delLogicServerInfo(EServerType serverType, ServerID serverID);
    BCLib::uint8 _getLogicServerInfo(SFLib::Message::SPeerServerInfo* serverList);

    virtual void _setExternalServerInfo(EServerType serverType, ServerID serverID);
    virtual void _delExternalServerInfo(EServerType serverType, ServerID serverID);
    BCLib::uint8 _getExternalServerInfo(SFLib::Message::SPeerServerInfo* serverList);

private:
    bool _sendMsgToGW(const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);

private:
    ServerID m_gatewayServerID;
    BCLib::Network::TcpStubID m_gameClientStubID;
    SFLib::CommonServer::CTcpStubPtr m_gameClientStub;

    std::map<EServerType, ServerID> m_logicServerTypeMap;
    BCLib::Utility::CMutex  m_mutexLogicServerTypeMap;

	std::map<EServerType, ServerID> m_externalServerTypeMap;
	BCLib::Utility::CMutex  m_mutexExternalServerTypeMap;

    ServerType m_resLeaveServerType;
    SFLib::Message::SMsgXS2XSResLeaveServer m_resLeaveServerMsg;

	//
    friend class CMasterClient;
    friend class CLogicStub;
    friend class CLogicClient;
    friend class CLogicServer;
};
typedef BCLib::Utility::CSPointer<CNetPeer> CNetPeerPtr;
}//Logic
}//SFLib

#endif//__SFLIB_LOGICSERVER_NETPEER_H__
