//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   SSLib/message/msgTypeSrv.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SSLIB_MESSAGE_MSGTYPESRV_H__
#define __SSLIB_MESSAGE_MSGTYPESRV_H__

#include <BCLib/framework/msgType.h>

namespace RN
{

//SSLib �� EMsgTypeͳһ����
//������ֻ��׷�ӣ�������������ͻ�ɾ������
enum EMsgType
{
    EMT_ACCOUNTSERVER = BCLib::Message::EMT_EXTEND,
    EMT_ACCOUNTCLIENT,
    EMT_EXTEND,
};

}//RN

#endif//__SSLIB_MESSAGE_MSGTYPESRV_H__
