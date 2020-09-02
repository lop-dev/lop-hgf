//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   platformServer/platformServer.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#include "platformServer.h"
#include "platformApp.h"
#include <iostream>

#include <BCLib/framework/sysConfig.h>
#include <BCLib/utility/io/directoryInfo.h>
#include <BCLib/utility/io/xmlFile.h>
#include <BCLib/utility/convert.h>
#ifdef WIN32
#include <MWLib/crashDump/crashDump.h>
#endif//WIN32
#include <SFLib/commonServer/msgLabel.h>
#include <SFLib/commonServer/tcpStubMgr.h>
#include <SHLib/commonDefine/logFile.h>
#include <SHLib/utility/svnInfo.h>
#include <SHLib/commonDefine/stringFilterWrap.h>
#include <SHLib/staticDataSystem/staticDataSystem.h>
#include <PELib/commonDefine/baseDef.h>
#include <SFLib/commonServer/netPeerMgr.h>
#include <SFLib/externalServer/netPeerMgr.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
BOOL WINAPI CtrlCHandler(DWORD CtrlType)
{
    CPlatformServer::singleton().setValid(false);
    //!ֻ��Holdס5S
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

BCLIB_FW_MAIN(CPlatformServer::main);

BCLIB_SINGLETON_DEFINE(CPlatformServer);

CPlatformServer::CPlatformServer()
    : SFLib::External::CExternalServer("PlatformServer")
{
    PELib::setRedisSystem(&MWLib::Redis::CRedisSystem::singleton());
    PELib::setNetPeerMgr(&SFLib::External::CNetPeerMgr::singleton());
    PELib::setCommonServer(this);
}

CPlatformServer::~CPlatformServer()
{
}

bool CPlatformServer::loadAllTable()
{
    //���ز߻������ļ�
    if (!SHLib::CStaticDataSystem::singleton().loadAllTable("../../../gameplay/table/"))
    {
        BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "load All Table error.");
        return false;
    }

    SHLib::CStaticDataSystem::singleton().init();


    return true;
}

bool CPlatformServer::_initConfig()
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
        std::cerr << "loadConfigFile " << configPath << "config.ini fail." << std::endl;
        return false;
    }


    std::string logFile = BCLib::Framework::CSysConfig::singleton()["LogFile"];
    if (logFile.empty() || logFile == "") {
        logFile = BCLib::Framework::CSysConfig::singleton()["platformServer/LogFile"];
        //if (logFile.empty() || logFile == "") {
            //logFile = "platformServer.log";
        logFile = "platformServer_" + BCLib::Utility::CConvert::toStringA(getpid()) + ".log";
        BCLib::Framework::CSysConfig::singleton()["platformServer/LogFile"] = logFile;
        //}
    }
    else {
        BCLib::Framework::CSysConfig::singleton()["platformServer/LogFile"] = logFile;
    }

    std::string logLevel = BCLib::Framework::CSysConfig::singleton()["platformServer/LogLevel"];
    if (logLevel.empty() || logLevel == "") {
        logLevel = "debug";
        BCLib::Framework::CSysConfig::singleton()["platformServer/LogLevel"] = logLevel;
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


    return true;
}

int CPlatformServer::main()
{
#ifndef WIN32  
    daemon(1, 1);
#endif

    SetupDefaultDirectory();

#if defined(_WIN32)
    MWLib::CrashDump::SetupCrashDump(SHLib::GetDumpFileName, NULL, MiniDumpWithFullMemory);
#endif

    MSLib::registerAllMsg2StrFunc();

    bool ret = CPlatformServer::singleton()._initConfig();
    if (!ret)
    {
        return -1;
    }

    bool loadTableFlag = CPlatformServer::singleton().loadAllTable();
    if (!loadTableFlag)
    {
        return -1;
    }

#ifdef _DEBUG
    BCLIB_LOG_SYSTEM(SHLib::ELOGMODULE_SHLIB_DEFAULT, "���� SuperLog Server Debug ......");
    //BCLIB_LOG_INFOR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "-------------��ʼ��ӡ��ǰ��������---------------");
    //BCLib::Framework::CSysConfig::singleton().showAllData();
    //BCLIB_LOG_INFOR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "-------------������ӡ��ǰ��������---------------");
#else
    BCLIB_LOG_SYSTEM(SHLib::ELOGMODULE_SHLIB_DEFAULT, "���� SuperLog Server Release ......");
#endif//_DEBUG

    return CPlatformServer::singleton()._main();
}

bool CPlatformServer::_init()
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
    if (!LOP::CPlatformApp::singleton().init())
    {
        BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "app init failed");
        return false;
    }
    LOP::CPlatformApp::singleton().start();
    ntfInitSuccess();
    BCLIB_LOG_SYSTEM(SHLib::ELOGMODULE_SHLIB_DEFAULT, "-------------platformServer�����ɹ�---------------");
    return true;
}

bool CPlatformServer::_callback()
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

int CPlatformServer::_final()
{
    if (LOP::CPlatformApp::singleton().isRunning()) {
        LOP::CPlatformApp::singleton().terminate();
        LOP::CPlatformApp::singleton().join();
    }

    int res = SFLib::External::CExternalServer::_final();
    return res;
}
