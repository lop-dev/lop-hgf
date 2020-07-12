//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/task.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_TASK_H__
#define __BCLIB_UTILITY_TASK_H__

#include <BCLib/utility/baseDef.h>
#include <BCLib/utility/ptrQueue.h>
#include <BCLib/utility/pointer.h>
#include <BCLib/utility/thread/mutex.h>
#include <BCLib/utility/spointer.h>

namespace BCLib
{
namespace Utility
{
//////////////////////////////////////////////////////////////////////////
/// @brief ����
//////////////////////////////////////////////////////////////////////////
class BCLIB_UTILITY_API CTask : public CRefCnt
{
public:
    virtual ~CTask()
    {
    }
    virtual void executeTask()
    {
    };
};
typedef CSPointer<CTask> CTaskSPtr;

//////////////////////////////////////////////////////////////////////////
/// @brief ������У����������1000������
//////////////////////////////////////////////////////////////////////////
class BCLIB_UTILITY_API CTaskQueue
{
protected:
    virtual ~CTaskQueue()
    {
    }
    virtual bool _isReady()
    {
        return true;
    }
    virtual bool _overRedLine()
    {
        return m_taskQueue.size() >= 1000;
    }

    virtual CTaskSPtr _popTask()
    {
        CTaskSPtr task = m_taskQueue.pop();
        if(task == NULL)
        {
            return NULL;
        }
        return task;
    }

    uint32 getSize()
    {
        return m_taskQueue.size();
    }

private:
    CPtrQueue<CTaskSPtr> m_taskQueue;

public:
    friend class CTaskPool;
};

//////////////////////////////////////////////////////////////////////////
/// @brief ������г�
//////////////////////////////////////////////////////////////////////////
class BCLIB_UTILITY_API CTaskPool
{
public:
    CTaskPool();
    virtual ~CTaskPool();

    /// @brief ��Ӷ��е����г��У��̰߳�ȫ
    /// @return void
    /// @param taskQueue
    void addQueue(const CTaskQueue* taskQueue);
    /// @brief ������񣬲����ķ����ĸ�������У��̰߳�ȫ
    /// @return bool
    /// @param task
    bool addTask(const CTaskSPtr& task);
    /// @brief
    /// @return void
    void clear();

private:
    std::vector<CTaskQueue*> m_taskQueueList;
    uint32 m_countTask;
    CMutex m_mutex;
};
}//Utility
}//BCLib
#endif//__BCLIB_UTILITY_TASK_H__
