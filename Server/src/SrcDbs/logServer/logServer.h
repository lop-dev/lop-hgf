//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   logServer/logServer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_LOGSERVER_LOGSERVER_H__
#define __LOP_LOGSERVER_LOGSERVER_H__

#include <BCLib/utility/version.h>
#include <BCLib/utility/singleton.h>
#include <SFLib/logicServer/logicServer.h>
#include <MSLib/commonDefine/message.h>
#include <STLib/commonDefine/sfCallback.h>
#include <STLib/commonDefine/baseDef.h>
#include <PBLib/protobuf/opConfig.pb.h>

class CLogServer : public SFLib::Logic::CLogicServer
{
    BCLIB_SINGLETON_DECLARE(CLogServer);

protected:
    CLogServer();
    virtual ~CLogServer();

public:
    virtual SFLib::EServerType getServerType()
    {
        return (SFLib::EServerType)MSLib::ELGCSERVER_LOG;
    }

    virtual std::string getServerVersion()
    {
        return STLIB_VERSION_TEXT; // BCLIB_VERSION_TEXT; 
    }

    const PBLib::COpConfig& getOpConfig() { return m_opConfig; }

    bool reloadAllTable();
protected:
    bool _initConfig();
    bool loadAllTable();

public:
    static int main();

protected:
    virtual bool _init();
    virtual bool _callback();
    virtual int _final();

    SFCB_SERVER_INIT;
    SFCB_SERVER_ENTER;
    SFCB_SERVER_LEAVE;
    SFCB_SERVER_SAVE;
    SFCB_SERVER_CLOSE;

    SFCB_PEER_CREATE;
    SFCB_PEER_ENTER;
    SFCB_PEER_LEAVE;
    SFCB_PEER_REMOVE;

private:
    PBLib::COpConfig m_opConfig;
};

#endif //__LOP_LOGSERVER_LOGSERVER_H__


