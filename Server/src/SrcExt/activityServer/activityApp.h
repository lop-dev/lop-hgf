//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   activityServer/activityApp.h
//  author:     League of Perfect
/// @brief	
/// 
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_ACTIVITYSERVER_ACTIVITYAPP_H__
#define __LOP_ACTIVITYSERVER_ACTIVITYAPP_H__

#include <BCLib/utility/singleton.h>
#include <BCLib/framework/frameTime.h>
#include <SFLib/externalServer/externalApp.h>

namespace LOP
{

    class CActivityApp : public SFLib::External::CExternalApp
    {
        BCLIB_SINGLETON_DECLARE(CActivityApp);

    protected:
        CActivityApp();
        virtual ~CActivityApp();

    public:
        bool init();

    protected:
        virtual bool _init();
        virtual bool _callback();
        virtual int _final();
        virtual void _update();

    private:
        BCLib::Framework::CFrameTime m_frameTime;
        static BCLib::Utility::CSteadyTime s_SteadyTime;
        static BCLib::Utility::CDelayTimer s_TenSec;  //10√Î
        static BCLib::Utility::CDelayTimer s_ThreeSec;//3√Î
        static BCLib::Utility::CDelayTimer s_TenMin;	//30∑÷÷”
    };

}//namespace LOP

#endif //__LOP_ACTIVITYSERVER_ACTIVITYAPP_H__
