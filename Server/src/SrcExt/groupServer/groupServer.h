//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   groupServer/groupServer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_GROUPSERVER_GROUPSERVER_H__
#define __LOP_GROUPSERVER_GROUPSERVER_H__

#include <BCLib/utility/version.h>
#include <BCLib/utility/singleton.h>
#include <SFLib/externalServer/externalServer.h>
#include <MSLib/commonDefine/message.h>
//#include <BCLib/database/dbInfo.h>
#include <SHLib/commonDefine/baseDef.h>
#include <SHLib/commonDefine/sfCallback.h>

class CGroupServer : public SFLib::External::CExternalServer
{
    BCLIB_SINGLETON_DECLARE(CGroupServer);

protected:
    CGroupServer();
    virtual ~CGroupServer();

public:
    virtual SFLib::EServerType getServerType()
    {
		return (SFLib::EServerType)MSLib::EEXTSERVER_PLATFORM;
    }

    virtual std::string getServerVersion() 
    { 
        return SHLIB_VERSION_TEXT; // BCLIB_VERSION_TEXT; 
    }

protected:
    bool _initConfig();
	bool loadAllTable();

public:
    static int main();


protected:
    virtual bool _init();
    virtual bool _callback();
    virtual int _final();

	SFCB_PEER_ENTER;
	SFCB_PEER_LEAVE;
};

#endif //__LOP_GROUPSERVER_GROUPSERVER_H__


