//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   accountServer/accountServer/databaseTask/task/accountAuthTask.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#include <sstream>
#include <BCLib/utility/logFile.h>
#include <BCLib/utility/convert.h>
#include <PELib/protoext/accountAuth.pe.h>
#include "accountAuthTask.h"
#include "../databaseTaskMgr.h"

namespace RN
{
namespace AccountServer
{

CDATABASETASK_SUBCLASS_DEFINE(InsertAccountAuth, PBLib::CAccountAuth, EDB_TASK_TYPE_INSERT_ACCOUNT_AUTH)
{
    CDATABASETASK_SUBCLASS_DEFINE_REPLY_Variable;

	std::string strName = m_ptBuf.accountname();
	if (strName == "")
	{
		m_errCode = BCLib::Database::EDB_TASK_ERROR_ILLEGAL_STRING;
		return false;
	}

	BCLib::Utility::CStringA tmpName = strName;
	hashIndex(tmpName, strDBIndex, strTBIndex);
	strDBName = getDBName(strDBIndex);
	strTBName = "AccountAuth" + strTBIndex;

	// 打印一下提示日志
	strName = "";
	BCLib::Utility::CConvert::utf8ToGB2312(strName, m_ptBuf.accountname());
	BCLIB_LOG_SYSTEM(BCLib::ELOGMODULE_DEFAULT, "InsertAccountAuth : %s (%s, %s)", strName.c_str(), strDBName.c_str(), strTBName.c_str());

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_UseDB;

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_SENTENCE_SELECT_CAccountAuth(m_ptBuf);
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader;
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader_Check(false);

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_SENTENCE_INSERT_CAccountAuth(m_ptBuf);
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteNonQuery;

	//
	sqlSentence.str("");
	sqlSentence << "SELECT LAST_INSERT_ID() AS AccountID";

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader;
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader_Check(true);

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader_Next;
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ReadUint64(m_ptBuf, accountid);
	BCLIB_SAFE_DELETE(pDataReader);

	if (m_ptBuf.accountid() == 0)
	{
		m_errCode = BCLib::Database::EDB_TASK_ERROR_INSERT_RECORD;
		return false;
	}

	m_errCode = BCLib::Database::EDB_TASK_ERROR_OK;
    return true;
}

CDATABASETASK_SUBCLASS_DEFINE(SelectAccountAuth, PBLib::CAccountAuth, EDB_TASK_TYPE_SELECT_ACCOUNT_AUTH)
{
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_Variable;

	std::string strName = m_ptBuf.accountname();
	if (strName == "")
	{
		m_errCode = BCLib::Database::EDB_TASK_ERROR_ILLEGAL_STRING;
		return false;
	}

	BCLib::Utility::CStringA tmpName = strName;
	hashIndex(tmpName, strDBIndex, strTBIndex);
	strDBName = getDBName(strDBIndex);
	strTBName = "AccountAuth" + strTBIndex;

	// 打印一下提示日志
	strName = "";
	BCLib::Utility::CConvert::utf8ToGB2312(strName, m_ptBuf.accountname());
	BCLIB_LOG_SYSTEM(BCLib::ELOGMODULE_DEFAULT, "SelectAccountAuth : %s (%s, %s)", strName.c_str(), strDBName.c_str(), strTBName.c_str());

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_UseDB;

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_SENTENCE_SELECT_CAccountAuth(m_ptBuf);
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader;
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader_Check(true);

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader_Next;
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteReader_CAccountAuth(m_ptBuf);

	BCLIB_SAFE_DELETE(pDataReader);

	m_errCode = BCLib::Database::EDB_TASK_ERROR_OK;
	return true;
}

CDATABASETASK_SUBCLASS_DEFINE(UpdateAccountAuth, PBLib::CAccountAuth, EDB_TASK_TYPE_UPDATE_ACCOUNT_AUTH)
{
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_Variable;

	std::string strName = m_ptBuf.accountname();
	if (strName == "")
	{
		m_errCode = BCLib::Database::EDB_TASK_ERROR_ILLEGAL_STRING;
		return false;
	}

	BCLib::Utility::CStringA tmpName = strName;
	hashIndex(tmpName, strDBIndex, strTBIndex);
	strDBName = getDBName(strDBIndex);
	strTBName = "AccountAuth" + strTBIndex;

	// 打印一下提示日志
	strName = "";
	BCLib::Utility::CConvert::utf8ToGB2312(strName, m_ptBuf.accountname());
	BCLIB_LOG_SYSTEM(BCLib::ELOGMODULE_DEFAULT, "UpdateAccountAuth : %s (%s, %s)", strName.c_str(), strDBName.c_str(), strTBName.c_str());

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_UseDB;

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_SENTENCE_UPDATE_CAccountAuth(m_ptBuf);
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteNonQuery;

	m_errCode = BCLib::Database::EDB_TASK_ERROR_OK;
	return true;
}

CDATABASETASK_SUBCLASS_DEFINE(DeleteAccountAuth, PBLib::CAccountAuth, EDB_TASK_TYPE_DELETE_ACCOUNT_AUTH)
{
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_Variable;

	std::string strName = m_ptBuf.accountname();
	if (strName == "")
	{
		m_errCode = BCLib::Database::EDB_TASK_ERROR_ILLEGAL_STRING;
		return false;
	}

	BCLib::Utility::CStringA tmpName = strName;
	hashIndex(tmpName, strDBIndex, strTBIndex);
	strDBName = getDBName(strDBIndex);
	strTBName = "AccountAuth" + strTBIndex;

	// 打印一下提示日志
	strName = "";
	BCLib::Utility::CConvert::utf8ToGB2312(strName, m_ptBuf.accountname());
	BCLIB_LOG_SYSTEM(BCLib::ELOGMODULE_DEFAULT, "DeleteAccountAuth : %s (%s, %s)", strName.c_str(), strDBName.c_str(), strTBName.c_str());

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_UseDB;

	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_SENTENCE_DELETE_CAccountAuth(m_ptBuf);
	CDATABASETASK_SUBCLASS_DEFINE_REPLY_SQL_ExecuteNonQuery;

	m_errCode = BCLib::Database::EDB_TASK_ERROR_OK;
	return true;
}

}//AccountServer
}//RN