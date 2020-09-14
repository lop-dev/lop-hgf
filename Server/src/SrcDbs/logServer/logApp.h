//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   logServer/logApp.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_LOGSERVER_LOGAPP_H__
#define __LOP_LOGSERVER_LOGAPP_H__

#include <BCLib/utility/singleton.h>
#include <BCLib/framework/frameTime.h>
#include <SFLib/logicServer/logicApp.h>

namespace LOP
{

    class CLogApp : public SFLib::Logic::CLogicApp
    {
        BCLIB_SINGLETON_DECLARE(CLogApp);

    protected:
        CLogApp();
        virtual ~CLogApp();

    public:
        bool init();

        bool isClosing() { return m_isClosing; }
        void setClosing(bool bClosing) { m_isClosing = bClosing; }

    protected:
        virtual bool _init();
        virtual bool _callback();
        virtual int _final();

        virtual void _update();

    private:
        BCLib::Framework::CFrameTime m_frameTime;
        bool m_isClosing;

        static BCLib::Utility::CSteadyTime s_SteadyTime;
        static BCLib::Utility::CDelayTimer s_ThreeSec;//3√Î
        static BCLib::Utility::CDelayTimer s_OneSec;//3√Î
    };

}//namespace LOP

#endif //__LOP_LOGSERVER_LOGAPP_H__
