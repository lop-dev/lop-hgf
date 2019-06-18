//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   accountServer/accountServer/network/netStubMgr.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SSLIB_ACCOUNTSET_ACCOUNTSERVER_NETWORK_NETSTUBMGR_H__
#define __SSLIB_ACCOUNTSET_ACCOUNTSERVER_NETWORK_NETSTUBMGR_H__

#include <BCLib/utility/singleton.h>
#include <BCLib/network/tcp/tcpStubMgr.h>

namespace RN
{
namespace AccountServer
{

class CTcpStubMgr : public BCLib::Network::CTcpStubMgr
{
    BCLIB_SINGLETON_DECLARE(CTcpStubMgr);

public:
    CTcpStubMgr();
    virtual ~CTcpStubMgr();

};

}//AccountServer
}//RN

#endif//__SSLIB_ACCOUNTSET_ACCOUNTSERVER_NETWORK_NETSTUBMGR_H__
