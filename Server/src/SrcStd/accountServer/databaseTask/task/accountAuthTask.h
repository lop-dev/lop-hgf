//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   accountServer/accountServer/databaseTask/task/accountAuthTask.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_TASK_ACCOUNTAUTHTASK_H__
#define __SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_TASK_ACCOUNTAUTHTASK_H__

#include "../databaseTask.h"
#include <PBLib/protobuf/accountAuth.pb.h>

namespace RN
{
namespace AccountServer
{

CDATABASETASK_SUBCLASS_DECLARE(InsertAccountAuth, PBLib::CAccountAuth);
CDATABASETASK_SUBCLASS_DECLARE(SelectAccountAuth, PBLib::CAccountAuth);
CDATABASETASK_SUBCLASS_DECLARE(UpdateAccountAuth, PBLib::CAccountAuth);
CDATABASETASK_SUBCLASS_DECLARE(DeleteAccountAuth, PBLib::CAccountAuth);

}//AccountServer
}//RN
#endif//__SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_TASK_ACCOUNTAUTHTASK_H__
