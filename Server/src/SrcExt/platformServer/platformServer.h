//////////////////////////////////////////////////////////////////////
//  created:   
//  filename:   platformServer/platformServer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_PLATFORMSERVER_PLATFORMSERVER_H__
#define __LOP_PLATFORMSERVER_PLATFORMSERVER_H__

#include <BCLib/utility/version.h>
#include <BCLib/utility/singleton.h>
#include <SFLib/externalServer/externalServer.h>
#include <MSLib/commonDefine/message.h>
#include <SHLib/commonDefine/baseDef.h>
#include <SHLib/commonDefine/sfCallback.h>

class CPlatformServer : public SFLib::External::CExternalServer
{
    BCLIB_SINGLETON_DECLARE(CPlatformServer);

protected:
    CPlatformServer();
    virtual ~CPlatformServer();

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

#endif //__LOP_PLATFORMSERVER_PLATFORMSERVER_H__


