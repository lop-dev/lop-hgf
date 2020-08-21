//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   accountServer/accountServer/databaseTask/databaseTask.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_DATABASETASK_H__
#define __SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_DATABASETASK_H__

#include <BCLib/database/task/databaseTask.h>
#include <BCLib/database/connection.h>
#include <BCLib/framework/serviceID.h>
#include <BCLib/utility/string.h>
#include <BCLib/utility/hashMap.h>
#include <BCLib/network/baseDef.h>

namespace RN
{
namespace AccountServer
{

enum EDBTaskType
{
    EDB_TASK_TYPE_INVALID_VALUE,

	EDB_TASK_TYPE_INSERT_ACCOUNT_AUTH,
    EDB_TASK_TYPE_SELECT_ACCOUNT_AUTH,
    EDB_TASK_TYPE_UPDATE_ACCOUNT_AUTH,
    EDB_TASK_TYPE_DELETE_ACCOUNT_AUTH,

	EDB_TASK_TYPE_VERIFY_NAME_PWD,
	EDB_TASK_TYPE_INSERT_NAME_PWD,
};

typedef BCLib::uint16 EchoID;

class CTcpStub;

class CDatabaseTask : public BCLib::Database::CDatabaseTask
{
public:
    CDatabaseTask();
    virtual ~CDatabaseTask();

public:
    void setStubID(BCLib::Network::TcpStubID  stubID){m_stubID = stubID;}

    void setEchoID(EchoID echoID){m_echoID = echoID;}
    EchoID getEchoID(){return m_echoID;}

protected:
    BCLib::Network::TcpStubID   m_stubID;
    EchoID                      m_echoID;
};

//////////////////////////////////////////////////////////////////////////

#define CDATABASETASK_SUBCLASS_DECLARE(_KEYNAME_, _PTBUF_)																\
typedef BCLib::int32 (*_KEYNAME_##Reply)(BCLib::Network::TcpStubID, EchoID, BCLib::Database::EDBTaskResult, _PTBUF_);	\
class C##_KEYNAME_##Task : public CDatabaseTask																			\
{																														\
public:																													\
	C##_KEYNAME_##Task(_PTBUF_ ptBuf, _KEYNAME_##Reply);																\
	virtual ~C##_KEYNAME_##Task();																						\
																														\
	virtual bool excute(BCLib::Database::CConnectionMap &);																\
	virtual bool reply();																								\
																														\
private:																												\
	_PTBUF_ m_ptBuf;																									\
	_KEYNAME_##Reply  m_funcReply;																						\
};

//////////////////////////////////////////////////////////////////////////

#define CDATABASETASK_SUBCLASS_DEFINE(_KEYNAME_, _PTBUF_, _TYPE_)										\
C##_KEYNAME_##Task::C##_KEYNAME_##Task(_PTBUF_ ptBuf, _KEYNAME_##Reply reply)							\
:m_ptBuf(ptBuf)																							\
,m_funcReply(reply)																						\
{																										\
	m_taskType = _TYPE_;																				\
}																										\
																										\
C##_KEYNAME_##Task::~C##_KEYNAME_##Task()																\
{																										\
}																										\
																										\
bool C##_KEYNAME_##Task::reply()																		\
{																										\
	BCLib::int32	i32Ret = -1;																		\
	if (m_funcReply)																					\
	{																									\
		i32Ret = m_funcReply(m_stubID, m_echoID, (BCLib::Database::EDBTaskResult)m_errCode, m_ptBuf);	\
	}																									\
	return i32Ret > 0;																					\
}																										\
																										\
bool C##_KEYNAME_##Task::excute(BCLib::Database::CConnectionMap& mapConnections)

}//AccountServer
}//RN

#endif//__SSLIB_ACCOUNTSET_ACCOUNTSERVER_DATABASETASK_DATABASETASK_H__
