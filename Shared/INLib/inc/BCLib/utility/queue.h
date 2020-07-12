//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/queue.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_QUEUE_H__
#define __BCLIB_UTILITY_QUEUE_H__

#include <BCLib/utility/allocator.h>
#include <BCLib/utility/ptrQueue.h>

namespace BCLib
{
namespace Utility
{
//////////////////////////////////////////////////////////////////////////
/// @brief �����࣬����ͬʱ������ֵ��һ��ITEM��
//////////////////////////////////////////////////////////////////////////
template<typename TYPE, typename TEMPTYPE = void>
class CQueue
{
private:
    struct CQueueItem
    {
        uint32 m_dataSize;
        uint32 m_tempDataSize;
    };

public:
    virtual ~CQueue()
    {
        clear();
    }

    /// @brief ��data��tempData�󶨷��뵽������,����socket�е�readv/writev
    /// @return bool
    /// @param data
    /// @param dataSize
    /// @param tempData
    /// @param tempDataSize
    bool push(const TYPE* data, const uint32 dataSize, const TEMPTYPE* tempData = NULL, const uint32 tempDataSize = 0)
    {
        uint32 tempDataLen = tempDataSize;
        if(tempData == NULL)
        {
            tempDataLen = 0;
        }

        unsigned char* dataBuff = m_allocator.allocate(dataSize + tempDataLen + sizeof(CQueueItem));
        if(dataBuff == NULL)
        {
            return false;
        }

        CQueueItem* queueItem = (CQueueItem*)dataBuff;

        TYPE* dataQueueItem = (TYPE*)(dataBuff + sizeof(CQueueItem));
        queueItem->m_dataSize = dataSize;
        memcpy(dataQueueItem, data, dataSize);

        if(tempDataLen != 0)
        {
            TEMPTYPE* tempDataQueueItem = (TEMPTYPE*)(dataBuff + dataSize + sizeof(CQueueItem));
            queueItem->m_tempDataSize = tempDataLen;
            memcpy(tempDataQueueItem, tempData, tempDataLen);
        }
        else
        {
            queueItem->m_tempDataSize = 0;
        }

        m_prtQueue.push(queueItem);
        return true;
    }

    /// @brief �Ӷ�����ȡ��data��tempData,����socket�е�readv/writev
    /// @return int
    /// @param data
    /// @param tempData
    /// @param tempDataSize
    int get(TYPE** data, TEMPTYPE** tempData = NULL, uint32* tempDataSize = NULL)
    {
        if(m_prtQueue.empty())
        {
            return 0;
        }

        CQueueItem* queueItem = m_prtQueue.get();
        unsigned char* dataBuff = (unsigned char*)queueItem;

        TYPE* dataQueueItem = (TYPE*)(dataBuff + sizeof(CQueueItem));
        *data = dataQueueItem;

        if(queueItem->m_tempDataSize != 0)
        {
            TEMPTYPE* tempDataQueueItem = (TEMPTYPE*)(dataBuff + queueItem->m_dataSize + sizeof(CQueueItem));
            if(tempData != NULL)
            {
                *tempData = tempDataQueueItem;
            }
            if(tempDataSize != NULL)
            {
                *tempDataSize = queueItem->m_tempDataSize;
            }
        }
        else
        {
            if(tempData != NULL)
            {
                *tempData = NULL;
            }
            if(tempDataSize != NULL)
            {
                *tempDataSize = 0;
            }
        }

        return queueItem->m_dataSize;
    }

    /// @brief ̸������ͷ�����Զ������ڴ�
    /// @return void
    void pop()
    {
        if(m_prtQueue.empty())
        {
            return ;
        }
        CQueueItem* queueItem = m_prtQueue.get();
        m_allocator.deallocate((unsigned char*)queueItem, queueItem->m_dataSize + queueItem->m_tempDataSize + sizeof(CQueueItem));
        m_prtQueue.pop();
    }

    void clear()
    {
        while(!m_prtQueue.empty())
        {
            CQueueItem* queueItem = m_prtQueue.get();
            m_allocator.deallocate((unsigned char*)queueItem, queueItem->m_dataSize + queueItem->m_tempDataSize + sizeof(CQueueItem));
            m_prtQueue.pop();
        }
    }

    bool empty()
    {
        return m_prtQueue.empty();
    }

private:
    CPtrQueue<CQueueItem*> m_prtQueue;
    //�ڴ������
    CAllocatorUint8 m_allocator;
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_QUEUE_H__
