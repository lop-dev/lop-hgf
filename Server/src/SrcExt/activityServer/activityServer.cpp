//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   activityServer/activityServer.cpp
//  author:     League of Perfect
/// @brief	
/// 
//////////////////////////////////////////////////////////////////////
#include "activityServer.h"
#include <BCLib/framework/sysConfig.h>
#include <BCLib/utility/io/directoryInfo.h>
#include <BCLib/utility/io/xmlFile.h>
#include <BCLib/utility/convert.h>
#ifdef WIN32
#include <MWLib/crashDump/crashDump.h>
#else
#include <csignal>
#include <gperftools/profiler.h>
#endif//WIN32
#include <SFLib/commonServer/msgLabel.h>
#include <SFLib/commonServer/tcpStubMgr.h>
#include <SHLib/commonDefine/logFile.h>
#include <SHLib/utility/svnInfo.h>
#include <SHLib/commonDefine/stringFilterWrap.h>
#include <PELib/commonDefine/baseDef.h>
#include <SFLib/externalServer/netPeerMgr.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif
#include "activityApp.h"

//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
BOOL WINAPI CtrlCHandler(DWORD CtrlType)
{
    CActivityServer::singleton().setValid(false);
    //!ֻ��Holdס5S
    while (1)
    {
        ;
    }
    return TRUE;
}
#else
static void signalHandler(int signal)
{
    if (signal == SIGUSR1) {
        BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "gperf start!");
        ProfilerStart("activity.prof");
    }
    if (signal == SIGUSR2) {
        BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "gperf stop!");
        ProfilerStop();
    }
}
#endif//WIN32

static void SetupDefaultDirectory()
{
    std::string exeFullName = BCLib::Utility::CDirectoryInfo::getExeDirectory();
    BCLib::Utility::CDirectoryInfo::setCurDirectory(exeFullName);
}

//////////////////////////////////////////////////////////////////////////

BCLIB_FW_MAIN(CActivityServer::main);

BCLIB_SINGLETON_DEFINE(CActivityServer)

CActivityServer::CActivityServer()
    : SFLib::External::CExternalServer("activityServer")
{
    m_tableCount = 0;
    m_dbCount = 0;
    m_vecDBInfo.clear();
    //this->setServerID(60501);
    PELib::setRedisSystem(&MWLib::Redis::CRedisSystem::singleton());
    PELib::setNetPeerMgr(&SFLib::External::CNetPeerMgr::singleton());
    PELib::setCommonServer(this);
}

CActivityServer::~CActivityServer()
{
    ;
}

bool CActivityServer::_initConfig()
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

    bool rt = SFLib::External::CExternalServer::loadConfigFile(configPath + "config.ini");
    if (!rt)
    {
        return false;
    }

    std::string logFile = BCLib::Framework::CSysConfig::singleton()["LogFile"];
    if (logFile.empty() || logFile == "") {
        logFile = BCLib::Framework::CSysConfig::singleton()["activityServer/LogFile"];
        //if (logFile.empty() || logFile == ""){
            //logFile = "GameServer.log";
        logFile = "activityServer_" + BCLib::Utility::CConvert::toStringA(getpid()) + ".log";
        BCLib::Framework::CSysConfig::singleton()["activityServer/LogFile"] = logFile;
        // }
    }
    else {
        BCLib::Framework::CSysConfig::singleton()["activityServer/LogFile"] = logFile;
    }

    std::string logLevel = BCLib::Framework::CSysConfig::singleton()["activityServer/LogLevel"];
    if (logLevel.empty() || logLevel == "") {
        logLevel = "debug";
        BCLib::Framework::CSysConfig::singleton()["activityServer/LogLevel"] = logLevel;
    }

    std::string logFilePath = logPath + logFile;
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

    /*std::string serverDIStr = BCLib::Framework::CSysConfig::singleton()["activityServer/activityServerID"];
    this->setServerID(BCLib::Utility::CConvert::toUint16(serverDIStr));
    BCLIB_LOG_DEBUG(SHLib::ELOGMODULE_SHLIB_DEFAULT, "ServerID = %d ", this->getServerID());
    if (this->getServerID() == 0)
    {
        BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "ServerID = %d ", this->getServerID());
        return false;
    }*/
    std::string fullConfig = currpath + "/config/";
    if (BCLib::Utility::CDirectoryInfo::isExist(currpath + "/gameconfig/"))
    {
        fullConfig = currpath + "/gameconfig/";
    }

    //std::string strAvailability = BCLib::Framework::CSysConfig::singleton()["ActivityServer/Availability"];
    //if (strAvailability == "true")
    //{
    //	std::string strDbFile = BCLib::Framework::CSysConfig::singleton()["ActivityServer/DatabaseFile"];
    //	if (strDbFile.empty() || strDbFile == "")
    //	{
    //		strDbFile = "activityServerDB.xml";
    //	}
    //	strDbFile = fullConfig + strDbFile;

    //	if (!LOP::CDatabaseMgr::singleton().init(strDbFile))
    //	{
    //		BCLIB_LOG_INFOR(BCLib::ELOGMODULE_DEFAULT, "CDatabaseMgr init Failed!");
    //		return false;
    //	}
    //}

    std::string redisIp = BCLib::Framework::CSysConfig::singleton()["ActivityServer/ExternalRedisIp"];
    BCLib::Utility::CStringA  redisPortStr = (std::string)BCLib::Framework::CSysConfig::singleton()["ActivityServer/ExternalRedisPort"];
    int redisPort = BCLib::Utility::CConvert::toInt32(redisPortStr);
    std::string redisPasswd = BCLib::Framework::CSysConfig::singleton()["ActivityServer/ExternalRedisPasswd"];
    MWLib::Redis::CRedisSystem::singleton().setInfo(redisIp, redisPort, redisPasswd, MWLib::Redis::E_REDIS_SERVERTYPE_EXTERNAL);

    return true;
}

int CActivityServer::main()
{
#ifndef WIN32  
    daemon(1, 1);
#endif

    SetupDefaultDirectory();

#if defined(_WIN32)
    MWLib::CrashDump::SetupCrashDump(SHLib::GetDumpFileName, NULL, MiniDumpWithFullMemory);
#endif

    MSLib::registerAllMsg2StrFunc();

    CActivityServer::singleton()._initConfig();

#ifdef _DEBUG
    BCLIB_LOG_SYSTEM(SHLib::ELOGMODULE_SHLIB_DEFAULT, "���� Activity Server Debug ......");
    //BCLIB_LOG_INFOR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "-------------��ʼ��ӡ��ǰ��������---------------");
    //BCLib::Framework::CSysConfig::singleton().showAllData();
    //BCLIB_LOG_INFOR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "-------------������ӡ��ǰ��������---------------");
#else
    BCLIB_LOG_SYSTEM(SHLib::ELOGMODULE_SHLIB_DEFAULT, "���� Activity Server Release ......");
#endif//_DEBUG

    return CActivityServer::singleton()._main();
}

bool CActivityServer::hasUnLawKeyWord(const std::string& strName) const
{
    return SHLib::CStringFilterWrap::singleton().hasUnLawKeyWord(strName);
}


bool CActivityServer::_init()
{
    //if(!LOP::CDatabaseMgr::singleton().init())
    //{
    //	BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "CNameManager::singleton().init() fail!!!");
    //	return false;
    //}

    if (!SFLib::External::CExternalServer::_init()) {
        BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "[SFLib::External::CExternalServer::_init()] failed");
        return false;
    }
    LOP::CActivityApp::singleton().init();
    LOP::CActivityApp::singleton().start();
    ntfInitSuccess();
    BCLIB_LOG_SYSTEM(SHLib::ELOGMODULE_SHLIB_DEFAULT, "-------------activityServer�����ɹ�---------------");
    return true;
}

bool CActivityServer::_callback()
{
    // 	if(!SFLib::External::CExternalServer::_recvMsg(true))
    // 	{
    // 		BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "MsgQueue POLL Failed!");
    // 		return false;
    // 	}
    // 
    // 	LOP::CMsgHandle::singleton().doParse();
    // 	BCLib::Utility::CThread::msleep(1);
    return SFLib::External::CExternalServer::_callback();
}

int CActivityServer::_final()
{
    if (LOP::CActivityApp::singleton().isRunning()) {
        LOP::CActivityApp::singleton().terminate();
        LOP::CActivityApp::singleton().join();
    }
    LOP::CActivityApp::singleton().final();

    int res = SFLib::External::CExternalServer::_final();
    return res;
}

