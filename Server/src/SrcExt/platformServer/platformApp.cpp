//////////////////////////////////////////////////////////////////////
//  created:    2020/08/26
//  filename:   billServer/billApp.cpp
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#include "platformApp.h"
#include "platformServer.h"
#include <BCLib/utility/dateTime.h>
#include <SHLib/commonDefine/logFile.h>
#include "msgGate.h"

namespace LOP
{

BCLib::Utility::CSteadyTime CPlatformApp::s_SteadyTime;
BCLib::Utility::CDelayTimer CPlatformApp::s_OneSec(1000, s_SteadyTime);
BCLib::Utility::CDelayTimer CPlatformApp::s_ThreeSec(3000, s_SteadyTime);
BCLib::Utility::CDelayTimer CPlatformApp::s_TenSec(10000, s_SteadyTime);

BCLIB_SINGLETON_DEFINE(CPlatformApp);

CPlatformApp::CPlatformApp()
{
}

CPlatformApp::~CPlatformApp()
{
}

bool CPlatformApp::init()
{
    /// TODO: add Logic Init here
    CMsgGate::singleton().init();

    return true;
}

bool CPlatformApp::_init()
{
    if (!SFLib::External::CExternalApp::_init())
    {
        return false;
    }
    return true;
}

bool CPlatformApp::_callback()
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

int CPlatformApp::_final()
{
    return SFLib::External::CExternalApp::_final();
}

void CPlatformApp::_update()
{
    /// TODO: add Logic update here
    m_frameTime.update();
    CMsgGate::singleton().update();

    BCLib::Utility::CSteadyTime now;
    if (s_ThreeSec(now))
    {
        CPlatformServer::singleton().checkMasterServer();
    }
    if (s_OneSec(now))
    {
        //CLogSystem::singleton().update();
    }
}

}//namespace LOP
