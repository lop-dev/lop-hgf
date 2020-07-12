//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/commonServer/netClient/commonClient.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_COMMONSERVER_NETCLIENT_COMMONCLIENT_H__
#define __SFLIB_COMMONSERVER_NETCLIENT_COMMONCLIENT_H__

#include <SFLib/commonServer/netClient/tcpClient.h>

namespace SFLib
{
namespace CommonServer
{
class SFLIB_COMMON_API CCommonClient : public CTcpClient
{
public:
    CCommonClient();
    virtual ~CCommonClient();

    virtual bool start();
    virtual void terminate();

    void setServerIP(const std::string& outerip, const std::string& innerip)
    {
        m_serverOuterIP = outerip; m_serverInnerIP = innerip;
    }
    std::string& getServerIP()
    {
        return m_serverIP;
    }

    void setServerPort(const BCLib::uint16 port)
    {
        m_serverPort = port;
    }
    BCLib::uint16 getServerPort()
    {
        return m_serverPort;
    }

protected:
    virtual bool _enterPoll();
    virtual bool _leavePoll();

    bool _connectToSrv();

private:
    std::string m_serverOuterIP;
    std::string m_serverInnerIP;
    std::string m_serverIP;
    BCLib::uint16 m_serverPort;
    bool m_bReconnect; // ���������ӵ�ʱ�������ʼ���Ӳ��ϣ���һֱ������ֱ������Ϊ��
	bool m_bLeavePoll; // ��¼�Ƿ��Ѿ��뿪Poll
};
typedef BCLib::Utility::CSPointer<CCommonClient> CCommonClientPtr;
}//CommonServer
}//SFLib

#endif//__SFLIB_COMMONSERVER_NETCLIENT_COMMONCLIENT_H__
