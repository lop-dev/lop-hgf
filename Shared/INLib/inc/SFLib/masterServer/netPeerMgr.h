//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/masterServer/netPeerMgr.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_MASTERSERVER_NETPEERMGR_H__
#define __SFLIB_MASTERSERVER_NETPEERMGR_H__

#include <BCLib/utility/singleton.h>
#include <BCLib/utility/uniqueID.h>
#include <SFLib/commonServer/netPeerMgr.h>
#include <SFLib/masterServer/netPeer.h>

namespace SFLib
{
namespace Master
{
class SFLIB_MASTER_API CNetPeerMgr : public SFLib::CommonServer::CNetPeerMgr
{
    BCLIB_SINGLETON_DECLARE(CNetPeerMgr);

public:
    CNetPeerMgr();
    virtual ~CNetPeerMgr();

    CNetPeerPtr getNetPeer(PeerID peerID);
	CNetPeerPtr getNetPeerByEntityID(EntityID entityID);

    BCLib::Utility::CUniqueID64* getAllocPeerID()
    {
        return &m_allocPeerID;
    }

    /// @brief 删除某个网关上所有的 Peer
    /// @return void
    /// @param gatewayServerID 网关的ServerID
    void delAllNetPeer(ServerID gatewayServerID);

    /// @brief 删除整个服务器上所有的 Peer
    /// @return void
    void delAllNetPeer();

private:
    BCLib::Utility::CUniqueID64 m_allocPeerID;
};
}//Master
}//SFLib

#endif//__SFLIB_MASTERSERVER_NETPEERMGR_H__
