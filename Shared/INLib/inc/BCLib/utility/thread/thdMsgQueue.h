//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/thread/thdMsgQueue.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_THREAD_THDMSGQUEUE_H__
#define __BCLIB_UTILITY_THREAD_THDMSGQUEUE_H__

#include <BCLib/utility/baseDef.h>

namespace BCLib
{
namespace Utility
{
class BCLIB_UTILITY_API CThdMsgQueue
{
protected:
    CThdMsgQueue()
    {
    }
    virtual ~CThdMsgQueue()
    {
    }

public:
    static bool create(HndThdMsgQueue& queHandle);
    static void remove(HndThdMsgQueue queHandle);

    //ͬ����ȡ��Ϣ
    // 0< �쳣
    // >0 �յ���Ϣ
    static int recv(HndThdMsgQueue queHandle, uint32* para1, uint16* para2, void** para3);
    // =0 û���յ���Ϣ
    static int recvAsync(HndThdMsgQueue queHandle, uint32* para1, uint16* para2, void** para3);

    //�첽������Ϣ
    static bool send(HndThdMsgQueue queHandle, uint32 para1, uint16 para2, void* para3);
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_THREAD_THDMSGQUEUE_H__
