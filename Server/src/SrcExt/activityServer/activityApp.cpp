//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   activityServer/activityApp.cpp
//  author:     League of Perfect
/// @brief	
/// 
//////////////////////////////////////////////////////////////////////
#include "activityApp.h"
#include <BCLib/utility/dateTime.h>
#include <SHLib/commonDefine/logFile.h>
#include "msgGate.h"
#include "activityServer.h"
#include <cmath>

namespace LOP
{
    BCLib::Utility::CSteadyTime CActivityApp::s_SteadyTime;
    BCLib::Utility::CDelayTimer CActivityApp::s_TenSec(10000, s_SteadyTime);
    BCLib::Utility::CDelayTimer CActivityApp::s_ThreeSec(3000, s_SteadyTime);
    BCLib::Utility::CDelayTimer CActivityApp::s_TenMin(600000, s_SteadyTime);

    BCLIB_SINGLETON_DEFINE(CActivityApp);

    CActivityApp::CActivityApp()
    {
    }

    CActivityApp::~CActivityApp()
    {
    }

    bool CActivityApp::init()
    {
        /// TODO: add Logic Init here
        CMsgGate::singleton().init();
        //从redis加载跨服活动数据
        //CActivitySystem::singleton().Init();
        return true;
    }

    bool CActivityApp::_init()
    {
        if (!SFLib::External::CExternalApp::_init())
        {
            return false;
        }
        return true;
    }

    bool CActivityApp::_callback()
    {
        if (!SFLib::External::CExternalApp::_callback())
        {
            return false;
        }
        BCLib::Utility::CSurveyTimer surveyTimer;
        surveyTimer.reset();
        m_frameTime.update();

        _update();

        //
        BCLib::int64 tempMs = surveyTimer.milliseconds();
        if (tempMs > 500)
        {
            BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "循环超出[%d]", tempMs);
        }
        return true;
    }

    int CActivityApp::_final()
    {
        return SFLib::External::CExternalApp::_final();
    }

    void CActivityApp::_update()
    {
        /// TODO: add Logic update here
        m_frameTime.update();
        CMsgGate::singleton().update();
        //CDatabaseTaskMgr::singleton().processTaskResults();

        BCLib::Utility::CSteadyTime now;
        if (s_ThreeSec(now))
        {
            CActivityServer::singleton().checkMasterServer();
        }

        if (s_TenSec(now))
        {
            //CActivitySystem::singleton().update();
        }
    }

}//namespace LOP
