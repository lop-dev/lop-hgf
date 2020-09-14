//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   logServer/logServer.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#include "logServer.h"
#include <BCLib/framework/sysConfig.h>
#include <BCLib/utility/io/directoryInfo.h>
#ifdef WIN32
#include <MWLib/crashDump/crashDump.h>
#endif//WIN32
#include <STLib/commonDefine/logFile.h>
#include <SFLib/commonServer/msgLabel.h>
#include <SFLib/commonServer/tcpStubMgr.h>
#include <SFLib/logicServer/netPeer.h>
#include <SFLib/logicServer/netPeerMgr.h>
#include <SFLib/commonServer/netMsgQueue.h>
#include <STLib/staticDataSystem/staticDataSystem.h>
#include <MSLib/message/entitySystemMsg.h>
#include <BCLib/database/connection.h>
#include <BCLib/database/dataReader.h>
#include <BCLib/database/databaseMgr.h>
#include <PELib/commonDefine/timingWheel.h>
#include <MSLib/commonDefine/sendMsgToDB.h>
#include "logApp.h"
#include <PELib/commonDefine/baseDef.h>
#include <SHLib/commonDefine/baseDef.h>
#include <BCLib/utility/convert.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
BOOL WINAPI CtrlCHandler(DWORD CtrlType)
{
    CLogServer::singleton().setValid(false);
    //!只能Hold住5S
    while (1)
    {
        ;
    }
    return TRUE;
}
#endif//WIN32

static void SetupDefaultDirectory()
{
    std::string exeFullName = BCLib::Utility::CDirectoryInfo::getExeDirectory();
    BCLib::Utility::CDirectoryInfo::setCurDirectory(exeFullName);
}

//////////////////////////////////////////////////////////////////////////

BCLIB_FW_MAIN(CLogServer::main);

BCLIB_SINGLETON_DEFINE(CLogServer)

CLogServer::CLogServer()
    : SFLib::Logic::CLogicServer("LogServer")
{
    m_notifyMaster = false;

    PELib::setRedisSystem(&MWLib::Redis::CRedisSystem::singleton());
    PELib::setNetPeerMgr(&SFLib::Logic::CNetPeerMgr::singleton());
    PELib::setCommonServer(this);

    PELib::CObjectOwner::m_FSendMsgToDB1 = ::MSLib::sendMsgToDB;
    PELib::CObjectOwner::m_FSendMsgToDB2 = ::MSLib::sendMsgToDB;
}

CLogServer::~CLogServer()
{
    ;
}

bool CLogServer::reloadAllTable()
{
    return loadAllTable();
}

bool CLogServer::_initConfig()
{
    std::string currpath = BCLib::Framework::CSysConfig::singleton()["workpath"];
    std::string configPath = BCLib::Framework::CSysConfig::singleton()["configpath"];
    if (configPath.empty())
    {
        configPath = currpath + "/config/";
    }
    BCLib::Utility::CDirectoryInfo::standardization(configPath);
    BCLib::Framework::CSysConfig::singleton()["configpath"] = configPath;

    std::string logPath = BCLib::Framework::CSysConfig::singleton()["logpath"];
    if (logPath.empty())
    {
        logPath = currpath + "/log/";
    }
    BCLib::Utility::CDirectoryInfo::standardization(logPath);
    BCLib::Framework::CSysConfig::singleton()["logpath"] = logPath;
    bool rt = SFLib::Logic::CLogicServer::loadConfigFile(configPath + "config.ini");
    if (!rt)
    {
        return false;
    }

    std::string logFile = BCLib::Framework::CSysConfig::singleton()["LogFile"];
    if (logFile.empty() || logFile == "") {
        //logFile = BCLib::Framework::CSysConfig::singleton()["LogServer/LogFile"];
        //if (logFile.empty() || logFile == ""){
            //logFile = "logServer.log";
        logFile = "LogServer_" + BCLib::Utility::CConvert::toStringA(getpid()) + ".log";
        BCLib::Framework::CSysConfig::singleton()["LogServer/LogFile"] = logFile;
        //}
    }
    else {
        BCLib::Framework::CSysConfig::singleton()["LogServer/LogFile"] = logFile;
    }

    std::string logLevel = BCLib::Framework::CSysConfig::singleton()["LogServer/LogLevel"];
    if (logLevel.empty() || logLevel == "") {
        logLevel = "debug";
        BCLib::Framework::CSysConfig::singleton()["LogServer/LogLevel"] = logLevel;
    }

    std::string logFilePath = logPath + logFile;
    BCLib::Utility::CDirectoryInfo::standardization(logFilePath);

    BCLib::Utility::CLogFile::singleton().setOutFile(logFilePath.c_str());
    BCLib::Utility::CLogFile::singleton().setModuleLevel(BCLib::ELOGMODULE_ALL, logLevel.c_str());

    bool isConsole = true;
    if (BCLib::Framework::CSysConfig::singleton()["console"] == "false") {
        isConsole = false;
    }
    BCLib::Utility::CLogFile::singleton().setOutConsole(isConsole);
#ifdef WIN32
    if (isConsole) {
        ::SetConsoleCtrlHandler(CtrlCHandler, TRUE);
    }
#endif//WIN32

    std::string redisIp = BCLib::Framework::CSysConfig::singleton()["LogServer/LogicRedisIp"];
    BCLib::Utility::CStringA  redisPortStr = (std::string)BCLib::Framework::CSysConfig::singleton()["LogServer/LogicRedisPort"];
    int redisPort = BCLib::Utility::CConvert::toInt32(redisPortStr);
    std::string redisPasswd = BCLib::Framework::CSysConfig::singleton()["LogServer/LogicRedisPasswd"];
    MWLib::Redis::CRedisSystem::singleton().setInfo(redisIp, redisPort, redisPasswd, MWLib::Redis::E_REDIS_SERVERTYPE_LOGIC);

    std::string redisIp2 = BCLib::Framework::CSysConfig::singleton()["LogServer/ExternalRedisIp"];
    BCLib::Utility::CStringA  redisPortStr2 = (std::string)BCLib::Framework::CSysConfig::singleton()["LogServer/ExternalRedisPort"];
    int redisPort2 = BCLib::Utility::CConvert::toInt32(redisPortStr2);
    std::string redisPasswd2 = BCLib::Framework::CSysConfig::singleton()["LogServer/ExternalRedisPasswd"];
    MWLib::Redis::CRedisSystem::singleton().setInfo(redisIp2, redisPort2, redisPasswd2, MWLib::Redis::E_REDIS_SERVERTYPE_EXTERNAL);

    MWLib::Redis::CRedisSystem::singleton().init(MWLib::Redis::E_REDIS_READ_ONLY);
    MWLib::Redis::CRedisSystem::singleton().isValid();

    BCLib::uint32 gameID = BCLib::Framework::CSysConfig::singleton().getValueInt("OpConfig/GameID");
    BCLib::uint32 opGameID = BCLib::Framework::CSysConfig::singleton().getValueInt("OpConfig/OpGameID");
    std::string serverID = BCLib::Framework::CSysConfig::singleton().getValueStr("OpConfig/ServerID");
    std::string region = BCLib::Framework::CSysConfig::singleton().getValueStr("OpConfig/Region");
    std::string timeZone = BCLib::Framework::CSysConfig::singleton().getValueStr("OpConfig/TimeZone");
    std::string language = BCLib::Framework::CSysConfig::singleton().getValueStr("OpConfig/Language");
    std::string country = BCLib::Framework::CSysConfig::singleton().getValueStr("OpConfig/Country");
    BCLib::uint32 serverType = BCLib::Framework::CSysConfig::singleton().getValueInt("OpConfig/ServerType");
    std::string strOpenTime = BCLib::Framework::CSysConfig::singleton().getValueStr("OpConfig/ServerOpenTime");
    BCLib::Utility::CDateTime openTime(strOpenTime);
    std::string serverKey = BCLib::Framework::CSysConfig::singleton().getValueStr("OpConfig/ServerKey");

    m_opConfig.set_gameid(gameID);
    m_opConfig.set_opgameid(opGameID);
    m_opConfig.set_serverid(serverID);
    m_opConfig.set_region(region);
    m_opConfig.set_timezone(timeZone);
    m_opConfig.set_language(language);
    m_opConfig.set_servertype(serverType);
    m_opConfig.set_country(country);
    m_opConfig.set_serveropentime(openTime.getTime());
    m_opConfig.set_serverkey(serverKey);

    std::string fullConfig = configPath + "/BldDbs/databaseServer/";
    BCLib::Utility::CDirectoryInfo::standardization(fullConfig);
    std::string strDbFile = BCLib::Framework::CSysConfig::singleton()["DatabaseServer/DatabaseFile"];
    if (strDbFile.empty() || strDbFile == "")
    {
        strDbFile = "DatabaseServerDB.xml";
    }
    strDbFile = fullConfig + strDbFile;

    /*if (!BCLib::Database::CDatabaseMgr::singleton().init(&LOP::CSnapshotDatabaseTaskMgr::singleton(), strDbFile))
    {
        BCLIB_LOG_ERROR(BCLib::ELOGMODULE_DEFAULT, "CDatabaseMgr init Failed!");
        return false;
    }*/

    return true;
}

bool CLogServer::loadAllTable()
{
    //加载策划配置文件
    if (!STLib::CStaticDataSystem::singleton().loadAllTable("../../../gameplay/table/"))
    {
        BCLIB_LOG_ERROR(STLib::ELOGMODULE_STLIB_DEFAULT, "load All Table error.");
        return false;
    }

    STLib::CStaticDataSystem::singleton().init();


    return true;
}
int CLogServer::main()
{
#ifndef WIN32  
    daemon(1, 1);
#endif

    SetupDefaultDirectory();

#if defined(_WIN32)
    MWLib::CrashDump::SetupCrashDump(SHLib::GetDumpFileName, NULL, MiniDumpWithFullMemory);
#endif

    MSLib::registerAllMsg2StrFunc();

    if (!CLogServer::singleton()._initConfig())
    {
        BCLIB_LOG_ERROR(STLib::ELOGMODULE_STLIB_DEFAULT, "initconfig Failed");
        return -1;
    }

    bool loadTableFlag = CLogServer::singleton().loadAllTable();
    if (!loadTableFlag)
    {
        BCLIB_LOG_ERROR(STLib::ELOGMODULE_STLIB_DEFAULT, "loadAllTable Failed");
        return -1;
    }
#ifdef _DEBUG
    BCLIB_LOG_SYSTEM(STLib::ELOGMODULE_STLIB_DEFAULT, "启动 Log Server Debug ......");
    //BCLIB_LOG_INFOR(STLib::ELOGMODULE_STLIB_DEFAULT, "-------------开始打印当前参数配置---------------");
    //BCLib::Framework::CSysConfig::singleton().showAllData();
    //BCLIB_LOG_INFOR(STLib::ELOGMODULE_STLIB_DEFAULT, "-------------结束打印当前参数配置---------------");
#else
    BCLIB_LOG_SYSTEM(STLib::ELOGMODULE_STLIB_DEFAULT, "启动 Log Server Release ......");
#endif//_DEBUG

    return CLogServer::singleton()._main();
}

bool CLogServer::_init()
{
    if (!SFLib::Logic::CLogicServer::_init()) {
        BCLIB_LOG_ERROR(STLib::ELOGMODULE_STLIB_DEFAULT, "[SFLib::Logic::CLogicServer::_init()] failed");
        return false;
    }

    if (!LOP::CLogApp::singleton().init())
    {
        BCLIB_LOG_ERROR(STLib::ELOGMODULE_STLIB_DEFAULT, "app init fail");
        return false;
    }

    LOP::CLogApp::singleton().start();
    ntfInitSuccess();

    BCLIB_LOG_SYSTEM(STLib::ELOGMODULE_STLIB_DEFAULT, "-------------LogServer启动成功---------------");
    return true;
}

bool CLogServer::_callback()
{
    return SFLib::Logic::CLogicServer::_callback();
}

int CLogServer::_final()
{
    if (LOP::CLogApp::singleton().isRunning()) {
        LOP::CLogApp::singleton().terminate();
        LOP::CLogApp::singleton().join();
    }

    MWLib::Redis::CRedisSystem::singleton().distroy();

    int res = SFLib::Logic::CLogicServer::_final();
    return res;
}
