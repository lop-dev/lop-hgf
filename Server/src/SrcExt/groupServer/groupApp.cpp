//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   billServer/billApp.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#include "groupApp.h"
#include "groupServer.h"
#include <BCLib/utility/dateTime.h>
#include <SHLib/commonDefine/logFile.h>
#include "msgGate.h"

namespace LOP
{
    BCLib::Utility::CSteadyTime CGroupApp::s_SteadyTime;
    BCLib::Utility::CDelayTimer CGroupApp::s_OneSec(1000, s_SteadyTime);
    BCLib::Utility::CDelayTimer CGroupApp::s_ThreeSec(3000, s_SteadyTime);
    BCLib::Utility::CDelayTimer CGroupApp::s_TenSec(10000, s_SteadyTime);

    BCLIB_SINGLETON_DEFINE(CGroupApp);

    CGroupApp::CGroupApp()
    {
    }

    CGroupApp::~CGroupApp()
    {
    }

    bool CGroupApp::init()
    {
        /// TODO: add Logic Init here
        CMsgGate::singleton().init();

        return true;
    }

    bool CGroupApp::_init()
    {
        if (!SFLib::External::CExternalApp::_init())
        {
            return false;
        }
        return true;
    }

    bool CGroupApp::_callback()
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
            BCLIB_LOG_ERROR(SHLib::ELOGMODULE_SHLIB_DEFAULT, "Ñ­»·³¬³ö[%d]", tempMs);
        }

        return true;
    }

    int CGroupApp::_final()
    {
        return SFLib::External::CExternalApp::_final();
    }

    void CGroupApp::_update()
    {
        /// TODO: add Logic update here
        m_frameTime.update();
        CMsgGate::singleton().update();

        BCLib::Utility::CSteadyTime now;
        if (s_ThreeSec(now))
        {
            CGroupServer::singleton().checkMasterServer();
        }

        if (s_OneSec(now))
        {
        }
    }

}//namespace LOP
