//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   logServer/logApp.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#include "logApp.h"
#include <BCLib/utility/dateTime.h>
#include <STLib/commonDefine/logFile.h>
#include <SFLib/commonServer/tcpStubMgr.h>

#include "logServer.h"
#include "msgGate.h"
#include <STLib/staticDataSystem/staticDataSystem.h>
#include <BCLib/utility/convert.h>
#include <STLib/utility/util.h>

#define SNAPSHOT_JOB_RUN_LIMIT_MINUTES 8*60

namespace LOP
{
    BCLib::Utility::CSteadyTime CLogApp::s_SteadyTime;
    BCLib::Utility::CDelayTimer CLogApp::s_ThreeSec(1000, s_SteadyTime);
    BCLib::Utility::CDelayTimer CLogApp::s_OneSec(3000, s_SteadyTime);

    BCLIB_SINGLETON_DEFINE(CLogApp);

    CLogApp::CLogApp()
        :m_isClosing(false)
    {
    }

    CLogApp::~CLogApp()
    {
    }

    bool CLogApp::init()
    {
        /// TODO: add Logic Init here
        CMsgGate::singleton().init();
        STLib::CStaticDataSystem::singleton().init();

        return true;
    }

    bool CLogApp::_init()
    {
        if (!SFLib::Logic::CLogicApp::_init())
        {
            return false;
        }
        return true;
    }

    bool CLogApp::_callback()
    {
        if (!SFLib::Logic::CLogicApp::_callback())
        {
            return false;
        }

        BCLib::Utility::CSurveyTimer surveyTimer;
        surveyTimer.reset();
        m_frameTime.update();

        _update();

        if (m_isClosing)
        {
            BCLib::uint32 uStubNum = SFLib::CommonServer::CTcpStubMgr::singleton().getStubNum();
            BCLib::uint32 careStubNum = 0;
            for (BCLib::uint8 i = SFLib::ESERVER_LOGIC_START; i < SFLib::ESERVER_MAX; i++)
            {
                if (i == MSLib::ELGCSERVER_GATEWAY || i == MSLib::ELGCSERVER_ANYXS)
                {
                    continue;
                }

                if (i <= SFLib::ESERVER_LOGIC_END)
                {
                    std::vector<SFLib::ServerID> serverIDs;
                    BCLib::uint64 groupID = CLogServer::singleton().getGroupID();;
                    SFLib::CommonServer::CServerMgr::singleton().getLogicServerIDs((SFLib::EServerType)i, serverIDs, false, groupID);
                    for (auto it = serverIDs.begin(); it != serverIDs.end(); ++it)
                    {
                        BCLib::Network::CTcpStubSPtr stubPtr = SFLib::CommonServer::CTcpStubMgr::singleton().getStubByServerID(*it);
                        if (stubPtr != NULL)
                        {
                            careStubNum++;
                            //break;
                        }
                    }
                }
                if (i >= SFLib::ESERVER_EXTERNAL_START)
                {
                    std::vector<SFLib::ServerID> serverIDs;
                    SFLib::CommonServer::CServerMgr::singleton().getExternalServerIDs((SFLib::EServerType)i, serverIDs, false);
                    for (auto it = serverIDs.begin(); it != serverIDs.end(); ++it)
                    {
                        BCLib::Network::CTcpStubSPtr stubPtr = SFLib::CommonServer::CTcpStubMgr::singleton().getStubByServerID(*it);
                        if (stubPtr != NULL)
                        {
                            careStubNum++;
                            //break;
                        }
                    }
                }

            }
            BCLIB_LOG_INFOR(STLib::ELOGMODULE_STLIB_DEFAULT, "安全退出 careStubNum[%d]", careStubNum);
            //if (uStubNum <= 0)
            if (careStubNum <= 0)
            {
                CLogServer::singleton().setValid(false);
                CLogServer::singleton().terminate();
            }
        }

        //
        BCLib::int64 tempMs = surveyTimer.milliseconds();
        if (tempMs > 500)
        {
            BCLIB_LOG_ERROR(STLib::ELOGMODULE_STLIB_DEFAULT, "循环超出[%d]", tempMs);
        }

        //if (SFLib::CommonServer::CNetMsgQueueBySFMsgLabel::singleton().empty())
        //{
        //BCLib::Utility::CThread::msleep(1);
        //}
        BCLib::Utility::CThread::msleep(1);


        return true;
    }

    int CLogApp::_final()
    {
        return SFLib::Logic::CLogicApp::_final();
    }

    void CLogApp::_update()
    {
        /// TODO: add Logic update here
        m_frameTime.update();
        CMsgGate::singleton().update();
        //CMsgHandle::singleton().doParse();

        BCLib::Utility::CSteadyTime now;
        if (s_ThreeSec(now))
        {
            CLogServer::singleton().checkMasterServer();
        }
        if (s_OneSec(now))
        {
        }
    }

}//namespace LOP
