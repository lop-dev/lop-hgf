//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/framework/thdMsgLabel.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_FRAMEWORK_THDMSGLABEL_H__
#define __BCLIB_FRAMEWORK_THDMSGLABEL_H__

#include <BCLib/utility/baseDef.h>
#include <BCLib/framework/message.h>
#include <BCLib/framework/serviceID.h>

namespace BCLib
{
namespace Framework
{
#if defined(_WIN32)
#pragma pack (push, 1)
#elif defined(_LINUX)
#pragma pack (1)
#endif

struct BCLIB_FRAMEWORK_API SThdMsgLabel
{
public:
    SThdMsgLabel(uint32 lableSize = sizeof(SThdMsgLabel))
    :m_fromService(0)
    ,m_toService(0)
    ,m_sessionID(0)
    ,m_msgSize(0)
    ,m_labelSize(lableSize)
    {
        if(m_labelSize < sizeof(SThdMsgLabel))
        {
            m_labelSize = sizeof(SThdMsgLabel);
        }
    }

public:
    CServiceID m_fromService;   //��Ϣ������
    CServiceID m_toService;     //��Ϣ������
    uint32 m_sessionID;
    uint32 m_msgSize;   //��Ϣ��С

    uint32 getLabelSize()
    {
        return m_labelSize;
    }

protected:
    uint32 m_labelSize;
};

#if defined(_WIN32)
#pragma pack (pop)
#elif defined(_LINUX)
#pragma pack ()
#endif
}//Framework
}//BCLib

#endif//__BCLIB_FRAMEWORK_THDMSGLABEL_H__
