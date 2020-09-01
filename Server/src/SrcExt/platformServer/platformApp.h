//////////////////////////////////////////////////////////////////////
//  created:    2020/08/26
//  filename:   platformServer/platformApp.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_PLATFORMSERVER_PLATFORMAPP_H__
#define __LOP_PLATFORMSERVER_PLATFORMAPP_H__

#include <BCLib/utility/singleton.h>
#include <BCLib/framework/frameTime.h>
#include <SFLib/externalServer/externalApp.h>

namespace LOP
{

class CPlatformApp : public SFLib::External::CExternalApp
{
    BCLIB_SINGLETON_DECLARE(CPlatformApp);

protected:
    CPlatformApp();
    virtual ~CPlatformApp();

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
    static BCLib::Utility::CDelayTimer s_OneSec;
    static BCLib::Utility::CDelayTimer s_ThreeSec;//3√Î
    static BCLib::Utility::CDelayTimer s_TenSec;
};

}//namespace LOP

#endif //__LOP_PLATFORMSERVER_PLATFORMAPP_H__
