//////////////////////////////////////////////////////////////////////
//  created:    2012/08/20
//  filename:   logServer/msgGate.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __LOP_LOGSERVER_MSGGATE_H__
#define __LOP_LOGSERVER_MSGGATE_H__

#include <SFLib/commonServer/netMsgQueue.h>
#include <SFLib/commonDefine/msgGate.h>

namespace LOP
{

    class CMsgGate : public SFLib::CMsgGate, public SFLib::CommonServer::CNetMsgQueueBySFMsgLabelCallback
    {
        BCLIB_SINGLETON_DECLARE(CMsgGate);

    protected:
        CMsgGate();
        virtual ~CMsgGate();

    public:
        void init();
        void update();

        virtual bool parse(const SFLib::CommonServer::SSFMsgLabel& msgLabel, const SFLib::Message::SNetMessage* netMessage, const BCLib::uint32 netMessageSize);

    private:
        void _onSFCallback(const SFLib::Message::SNetMessage* msg);
    };

}//namespace LOP

#endif // __LOP_LOGSERVER_MSGGATE_H__
