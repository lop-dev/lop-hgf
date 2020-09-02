//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   activityServer/activityServer.h
//  author:     League of Perfect
/// @brief	
/// 
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_ACTIVITYSERVER_ACTIVITYSERVER_H__
#define __LOP_ACTIVITYSERVER_ACTIVITYSERVER_H__

#include <BCLib/utility/version.h>
#include <BCLib/utility/singleton.h>
#include <BCLib/database/dbInfo.h>
#include <SFLib/externalServer/externalServer.h>
#include <MSLib/commonDefine/message.h>
#include <SHLib/commonDefine/baseDef.h>

class CActivityServer : public SFLib::External::CExternalServer
{
    BCLIB_SINGLETON_DECLARE(CActivityServer);

protected:
    CActivityServer();
    virtual ~CActivityServer();

public:
    virtual SFLib::EServerType getServerType()
    {
        return (SFLib::EServerType)MSLib::EEXTSERVER_ACTIVITY;
    }

    virtual std::string getServerVersion()
    {
        return SHLIB_VERSION_TEXT; // BCLIB_VERSION_TEXT; 
    }

protected:
    bool _initConfig();

public:
    static int main();
    bool hasUnLawKeyWord(const std::string& strName) const;

protected:
    virtual bool _init();
    virtual bool _callback();
    virtual int _final();

private:
    std::vector<BCLib::Database::CDBInfo> m_vecDBInfo;
    BCLib::uint32 m_dbCount;
    BCLib::uint32 m_tableCount;

};

#endif //__LOP_ACTIVITYSERVER_ACTIVITYSERVER_H__


