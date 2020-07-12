//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/commonServer/netPeer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_COMMONSERVER_NETPEER_H__
#define __SFLIB_COMMONSERVER_NETPEER_H__

#include <BCLib/utility/pointer.h>
#include <SFLib/commonDefine/baseDef.h>
#include <SFLib/message/message.h>
#include <BCLib/utility/spointer.h>
#include <BCLib/utility/dateTime.h>

namespace SFLib
{
namespace CommonServer
{
enum EPeerState
{
    PEER_NULL,
    PEER_INIT,
    PEER_OK,
    PEER_LEAVE,
};

class SFLIB_COMMON_API CNetPeer : public BCLib::Utility::CRefCnt
{
public:
    CNetPeer();
    CNetPeer(PeerID netPeerID);
    virtual ~CNetPeer();

    PeerID getPeerID() const { return m_netPeerID; }
    EPeerState getState() { return m_peerState; }

	void setGroupID(GroupID groupID) { m_groupID = groupID; }
	GroupID getGroupID() const { return m_groupID; }

    void setOrgServerID(ServerID serverID) { m_orgServerID = serverID; }
    ServerID getOrgServerID() const { return m_orgServerID; }

	void setEntityID(EntityID entityID)	{ m_entityID = entityID; }
	EntityID getEntityID() const { return m_entityID; }

    virtual void init();
    virtual bool reqLeave();
    virtual void ackLeave();
    virtual void terminate();

    virtual bool serializeTo(BCLib::Utility::CStream& stream) const;
    virtual bool serializeFrom(BCLib::Utility::CStream& stream);

	void setOfflineTime(BCLib::Utility::CDateTime dtOffline) { m_dtOffline = dtOffline; }
	BCLib::Utility::CDateTime getOfflineTime() { return m_dtOffline; }

public:
	virtual ServerID getServerID(EServerType serverType);
    virtual EServerType getServerType(ServerID serverID);

    virtual bool sendMsgByType(ServerType serverType, const SFLib::Message::CNetMessage* msg);
    virtual bool sendMsgByType(ServerType serverType, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);

	virtual bool sendMsgToGC(const SFLib::Message::CNetMessage* msg);
	virtual bool sendMsgToGC(const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);

public:
	virtual BCLib::uint32 getLogicServerNum();

protected:
    virtual void _setLogicServerInfo(EServerType serverType, ServerID serverID);
    virtual void _delLogicServerInfo(EServerType serverType, ServerID serverID);

    virtual void _setExternalServerInfo(EServerType serverType, ServerID serverID);
    virtual void _delExternalServerInfo(EServerType serverType, ServerID serverID);

private:
    PeerID m_netPeerID;
	GroupID m_groupID;
    ServerID m_orgServerID;
	EntityID m_entityID;

    EPeerState m_peerState;
	BCLib::Utility::CDateTime m_dtOffline;

    friend class CExternalClient;
};

typedef BCLib::Utility::CSPointer<CNetPeer> CNetPeerPtr;
typedef std::vector<SFLib::CommonServer::CNetPeerPtr> CNetPeerPtrVec;
}//CommonServer
}//SFLib

#endif//__SFLIB_COMMONSERVER_NETPEER_H__
