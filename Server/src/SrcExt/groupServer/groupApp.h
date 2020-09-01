//////////////////////////////////////////////////////////////////////
//  created:    2020/08/26
//  filename:   groupServer/groupApp.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_GROUPSERVER_GROUPAPP_H__
#define __LOP_GROUPSERVER_GROUPAPP_H__

#include <BCLib/utility/singleton.h>
#include <BCLib/framework/frameTime.h>
#include <SFLib/externalServer/externalApp.h>

namespace LOP
{

class CGroupApp : public SFLib::External::CExternalApp
{
    BCLIB_SINGLETON_DECLARE(CGroupApp);

protected:
    CGroupApp();
    virtual ~CGroupApp();

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

#endif //__LOP_GROUPSERVER_GROUPAPP_H__
