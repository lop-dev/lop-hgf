//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   accountServer/accountServer/databaseTask/task/namePwdTask.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_TASK_NAMEPWDTASK_H__
#define __SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_TASK_NAMEPWDTASK_H__

#include "../databaseTask.h"
#include <PTLib/protobuf/accountVerify.pb.h>

namespace RN
{
namespace AccountServer
{

CDATABASETASK_SUBCLASS_DECLARE(VerifyNamePwd, PTBuf::CAccountVerify);
CDATABASETASK_SUBCLASS_DECLARE(InsertNamePwd, PTBuf::CAccountVerify);

}//AccountServer
}//RN

#endif//__SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_TASK_NAMEPWDTASK_H__
