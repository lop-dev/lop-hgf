//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   accountServer/accountServer/databaseTask/databaseTask.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////

#include <BCLib/utility/logFile.h>
#include <BCLib/security/hash.h>
#include <BCLib/database/databaseMgr.h>
#include "databaseTask.h"

namespace RN
{
namespace AccountServer
{

CDatabaseTask::CDatabaseTask()
:m_stubID(BCLib::Network::INVALID_TCPSTUBID)
,m_echoID(0)
{
}

CDatabaseTask::~CDatabaseTask()
{
}


}//AccountServer
}//RN