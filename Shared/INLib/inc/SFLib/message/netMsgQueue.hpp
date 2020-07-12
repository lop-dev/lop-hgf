//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SFLib/message/netMsgQueue.hpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SFLIB_MESSAGE_NETMSGQUEUE_HPP__
#define __SFLIB_MESSAGE_NETMSGQUEUE_HPP__

#include <BCLib/utility/thread/mutex.h>
#include <BCLib/utility/queue.h>
#include <SFLib/message/gameFrame.h>
#include <SFLib/message/message.h>

namespace SFLib
{
namespace Message
{
template<class TYPE>
class SFLIB_MESSAGE_TMP CNetMsgQueueCallback
{
public:
    virtual ~CNetMsgQueueCallback()
    {
    }

    virtual bool parse(const TYPE& key, const SFLib::Message::SNetMessage* netMessage, const BCLib::uint32 netMessageSize) = 0;
};

template<class TYPE>
class SFLIB_MESSAGE_TMP CNetMsgQueue
{
public:
	typedef BCLib::Utility::CQueue<SFLib::Message::SNetMessage, TYPE> MsgQueue;

	CNetMsgQueue()
	{
		m_queueChar = new MsgQueue();
	}

    virtual ~CNetMsgQueue()
    {
        //���������Ķ�����Ϊ����ʹ�ã�Ϊ��ֹ������ע�����������䣬�ڴ��⵽�˴����Ժ���
        //m_queueChar->clear();
		//BCLIB_SAFE_DELETE(m_queueChar);
    }

    virtual void push(const TYPE& tempData, const SFLib::Message::SNetMessage* netMessage, const BCLib::uint32 netMessageSize)
    {
        BCLib::Utility::CMutexFun fun(&m_mutex);
        m_queueChar->push(netMessage, netMessageSize, &tempData, sizeof(TYPE));
    }

    bool get(TYPE& tempData, SFLib::Message::SNetMessage** netMessage, BCLib::uint32* netMessageSize)
    {
        BCLib::Utility::CMutexFun fun(&m_mutex);
		TYPE* tempDateID = NULL;
        if(m_queueChar->empty())
        {
            return false;
        }
        *netMessageSize = m_queueChar->get(netMessage, &tempDateID);
        *tempData = *tempDateID;

        return true;
    }

    void pop()
    {
		BCLib::Utility::CMutexFun fun(&m_mutex);
        m_queueChar->pop();
    }

    bool empty()
    {
        BCLib::Utility::CMutexFun fun(&m_mutex);
        return m_queueChar->empty();
    }

    //************************************
    // Method:    doParse
    // ˼·1�Ǵӵ�ǰmsgQueue ȫ��pop ��push ����ʱ��msgQueue
    // ����������Ҫ��ȫ��Э�����¿�����(���BCLib::Utility::CQueue��
    // ��Ϊ����msgQueue
    // ʹ��new MsgQueue() �ᱣ֤����̵߳��� doParse�İ�ȫ�� �� 
    // ���ʼ��ֻ��һ���߳������ doParse�����Կ��Ǹ�Ϊ��Ա������
    // ���� new/delete MsgQueue�Ĵ���
    //************************************
    void doParse(CNetMsgQueueCallback<TYPE>& cb)
    {
		MsgQueue* popQueue = _swapMsgQueue();

		SFLib::Message::SNetMessage* netMsg;
		TYPE* tempData;

		while (!popQueue->empty())
		{
			BCLib::uint32 size = popQueue->get(&netMsg, &tempData);
			if (size == 0)
			{
				continue;
			}
			cb.parse(*tempData, netMsg, size);
			popQueue->pop();
		}

		BCLIB_SAFE_DELETE(popQueue);
    }

private:
	MsgQueue* _swapMsgQueue()
	{
		MsgQueue* newQueue = new MsgQueue();
		MsgQueue* tmp = NULL;
		BCLib::Utility::CMutexFun fun(&m_mutex);
		tmp = m_queueChar;
		m_queueChar = newQueue;
		return tmp;
	}

private:
    BCLib::Utility::CMutex m_mutex;
	MsgQueue *m_queueChar;
};
}//Message
}//SFLib

#endif//__SFLIB_MESSAGE_NETMSGQUEUE_HPP__
