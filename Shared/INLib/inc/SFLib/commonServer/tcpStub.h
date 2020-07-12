//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/commonServer/tcpStub.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_COMMONSERVER_TCPSTUB_H__
#define __SFLIB_COMMONSERVER_TCPSTUB_H__

#include <BCLib/utility/pointer.h>
#include <BCLib/utility/task.h>
#include <BCLib/utility/dateTime.h>
#include <BCLib/network/tcp/tcpStub.h>
#include <BCLib/framework/message.h>
#include <BCLib/framework/msgType.h>
#include <BCLib/framework/msgExecMgr.h>
#include <SFLib/message/gameFrame.h>
#include <SFLib/commonServer/netPeer.h>
#include <SFLib/commonServer/msgLabel.h>

namespace SFLib
{
namespace CommonServer
{
template<class TYPE>
class CAvgStat
{
public:
    CAvgStat()
    {
    }
    ~CAvgStat()
    {
    }

    void push(TYPE& data)
    {
        m_valueList.push_back(data);
    }

    void pop()
    {
        m_valueList.pop_front();
    }

    int size()
    {
        return (int)m_valueList.size();
    }

    TYPE getAvgValue()
    {
        if(m_valueList.size() < 3)
        {
            return 0;
        }
        TYPE countValue = 0;
        TYPE maxValue = 0;
        TYPE minValue = 0;

        typename std::list<TYPE>::iterator it = m_valueList.begin();
        maxValue = minValue = *it;

        for(; it != m_valueList.end(); ++it)
        {
            TYPE temp = *it;
            countValue += temp;

            if(temp < minValue)
            {
                minValue = temp;
            }
            if(temp > maxValue)
            {
                maxValue = temp;
            }
        }
        return (countValue - minValue - maxValue) / (m_valueList.size() - 2);
    }

private:
    std::list<TYPE> m_valueList;
};

typedef CAvgStat<BCLib::int32> CAvgStat32;

class SFLIB_COMMON_API CTcpStub : public BCLib::Framework::CMsgExecMgr, public BCLib::Network::CTcpStub
{
public:
    CTcpStub(const BCLib::Network::CTcpConnectionSPtr& netConn);
    virtual ~CTcpStub();

    virtual GroupID getGroupID()
    {
        return SFLib::INVALID_GROUP_ID;
    }

    ServerID getServerID() const
    {
        return m_serverID;
    }

    EServerType getServerType() const
    {
        return m_serverType;
    }

    /// @brief ֻ��������������ӵķ������ϲŻ���Ч(����GW)
    /// @return PeerID
    virtual PeerID getPeerID() const
    {
        return 0;
    }

    virtual BCLib::int32 send(const SFLib::Message::CNetMessage* msg);
    virtual BCLib::int32 send(const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);

    /// @brief ����peerID��Ҫ������Ϣ����ʧ�ܵ�ʱ�򴫸��߼���ʹ��
    /// @return �����ֽ��������ֵ
    virtual BCLib::int32 send(PeerID peerID, const SFLib::Message::CNetMessage* msg);

    /// @brief ����peerID��Ҫ������Ϣ����ʧ�ܵ�ʱ�򴫸��߼���ʹ��
    /// @return �����ֽ��������ֵ
    virtual BCLib::int32 send(PeerID peerID, const SFLib::Message::SNetMessage* msg, const BCLib::uint32 msgSize);

    std::string getDebugPrompt();

protected:
    virtual bool _cbParseMsg(const void* msgBuff, BCLib::uint32 msgSize);
            bool _cbParseMsg(SSFMsgLabel& msgLabel, SFLib::Message::SNetMessage* msg, BCLib::uint32 msgSize);
    virtual void _unhandledMsg(SSFMsgLabel& msgLabel, SFLib::Message::SNetMessage* msg, BCLib::uint32 msgSize);
    virtual bool _transformMsg(PeerID peerID, SFLib::Message::SNetMessage* msg, BCLib::uint32 msgSize);

    virtual void _cbTerminate();

    virtual bool _createMsgExecPtr(BCLib::uint16 type, BCLib::uint16 id, BCLib::Framework::CMsgExecPtr& msgExecPtr);
    virtual bool _createMsgExecPtr(BCLib::uint16 type, BCLib::Framework::CMsgExecPtr& msgExecPtr);
    virtual void _onXX2XSNtfServerType(BCLib::Framework::SThdMsgLabel* msgLabel, BCLib::Framework::SMessage* msg);

    void _setServerType(EServerType serverType)
    {
        m_serverType = serverType;
    }
    void _setServerID(ServerID serverID)
    {
        m_serverID = serverID;
    }

private:
    EServerType m_serverType;
    ServerID m_serverID;
    BCLib::Utility::CSurveyTimer m_pingTime;

    typedef std::vector<SFLib::Message::SMsgXX2XXNtfSubpackageMsg*> SubpackageMsgVec;
    typedef BCLib::Utility::CHashMap<BCLib::uint32, SubpackageMsgVec> SubpackageMsgMap;
    SubpackageMsgMap m_mapSubpackageMsg;
};
typedef BCLib::Utility::CSPointer<CTcpStub> CTcpStubPtr;
}//CommonServer
}//SFLib

#endif//__SFLIB_COMMONSERVER_TCPSTUB_H__
