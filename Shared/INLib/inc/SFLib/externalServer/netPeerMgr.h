//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/externalServer/netPeerMgr.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_EXTERNALSERVER_NETPEERMGR_H__
#define __SFLIB_EXTERNALSERVER_NETPEERMGR_H__

#include <BCLib/utility/singleton.h>
#include <SFLib/commonServer/netPeerMgr.h>
#include <SFLib/externalServer/netPeer.h>

namespace SFLib
{
namespace External
{
class SFLIB_EXTERNAL_API CNetPeerMgr : public SFLib::CommonServer::CNetPeerMgr
{
    BCLIB_SINGLETON_DECLARE(CNetPeerMgr);

public:
    CNetPeerMgr();
    virtual ~CNetPeerMgr();

    CNetPeerPtr getNetPeer(PeerID peerID);
	CNetPeerPtr getNetPeerByEntityID(EntityID entityID);

	/// @brief ��һ�������������ˣ��������������������ң��ᴥ��������cbPeerLeave()��cbPeerRemove()
	/// @return void
	/// @param stubID ��ߴ�������ڲ�������StubID
	void clear(BCLib::Network::TcpStubID stubID);

protected:
	virtual bool _serializeTo(BCLib::Utility::CStream& stream) const;
	virtual bool _serializeFrom(BCLib::Utility::CStream& stream);
};
}//External
}//SFLib

#endif//__SFLIB_EXTERNALSERVER_NETPEERMGR_H__
