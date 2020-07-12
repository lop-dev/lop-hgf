//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/network/tcp/tcpClient.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_NETWORK_TCP_TCPCLIENT_H__
#define __BCLIB_NETWORK_TCP_TCPCLIENT_H__

#include <BCLib/network/tcp/tcpSend.h>
#include <BCLib/network/sockAddr.h>


namespace BCLib
{
namespace Network
{
class CTcpConnectionMgr;
class CTcpConnection;
typedef BCLib::Utility::CSPointer<CTcpConnection> CTcpConnectionSPtr;

class BCLIB_NETWORK_API CTcpClient : public CTcpSend
{
    friend class CTcpClientCallback;
    friend class CTcpCltConnMgr;
public:
    CTcpClient(CEncrypt* encrypt = NULL, CCompress* compress = NULL);
    virtual ~CTcpClient();

	virtual bool start();
	virtual void join();

	virtual void terminate();
	virtual bool isRunning();

    /// @brief �ж��Ƿ�������������
    /// @return bool
    bool hasConnection() const;

    /// @brief �ж����������Ƿ���Ч
    /// @return bool
    bool isConnectionValid() const;

    const CSockAddr& getLocalAddr() const;
    const CSockAddr& getPeerAddr() const;

    std::string getMAC() const;

    bool setUsrKey(BCLib::uint64 usrKey);
    BCLib::uint64 getUsrKey() const;

    bool setSendDelay(BCLib::uint32 delay, BCLib::uint32 delayDiff);
    void setRTT(bool bOpen);
    bool isOpenRTT() const;
    BCLib::uint32 getRTTInMS() const;
    BCLib::int64 getConnectTimeInSec() const;
    BCLib::uint64 getTotalSendByte() const;
    BCLib::uint64 getTotalRecvByte() const;
    float getSendRateInKBPerSec() const;
    float getRecvRateInKBPerSec() const;

	/// @brief ���ӶԶ˵ķ�����
	/// @return bool true = ���ӳɹ�
	/// @param serverIP
	/// @param serverPort
	/// @param addToMgr ������ӳɹ�����Ҫʹ��������ʽ�շ���Ϣ���ʹ�falseֵ������trueֵ
    bool connect(const char* serverIP, BCLib::uint16 serverPort, bool addToMgr);
    void close();

    BCLib::int32 sendBlock(BCLib::Utility::CStream& stream);
    BCLib::int32 sendBlock(const void* msgBuf, BCLib::uint32 bufSize);
    BCLib::int32 recvBlock(void*& msgBuf, BCLib::int32 countMax = 0);

    BCLib::int32 send(BCLib::Utility::CStream& stream);
    BCLib::int32 send(const void* msgBuf, BCLib::uint32 bufSize);

protected:
    virtual bool _enterPoll();
    virtual bool _leavePoll();

    virtual bool _cbParseMsg(const void* msgBuff, BCLib::uint32 msgSize) = 0;
    //virtual bool _cbSendMsg(const BCLib::Network::CTcpConnectionSPtr& connPtr);
    virtual void _cbTerminate(const BCLib::Network::CTcpConnectionSPtr& connPtr);

    bool _addConn2Mgr();

protected:
    CEncrypt* m_encrypt;
    CCompress* m_compress;

private:
    BCLib::uint8 m_connState;
    CTcpConnectionSPtr m_connPtr;
    CTcpConnectionMgr* m_connMgr;
};
typedef BCLib::Utility::CSPointer<CTcpClient> CTcpClientSPtr;
}//Network
}//BCLib

#endif//__BCLIB_NETWORK_TCP_TCPCLIENT_H__
