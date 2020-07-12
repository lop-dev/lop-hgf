//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/framework/msgFreq.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_FRAMEWORK_MSGFREQ_H__
#define __BCLIB_FRAMEWORK_MSGFREQ_H__

#include <BCLib/framework/baseDef.h>
#include <BCLib/utility/singleton.h>
#include <BCLib/utility/hashMap.h>
#include <BCLib/framework/message.h>

namespace BCLib
{
namespace Framework
{

class CRecord;

//////////////////////////////////////////////////////////////////////////
/// @brief �����Ϣ����Ƶ�ʣ�����ʱ�䵥λ�Ǻ���
//////////////////////////////////////////////////////////////////////////
class BCLIB_FRAMEWORK_API CMsgFreq
{
    BCLIB_SINGLETON_DECLARE(CMsgFreq);

protected:
    CMsgFreq();
    virtual ~CMsgFreq();

public:
	/// @brief ������Ϣ���յ����Ƶ�ʣ���ÿ������յ�����
	/// @return void
	/// @param uniqueID ��Ϣ�ı��
	/// @param uFreq ����Ƶ��
    void setFreq(uint32 uniqueID, uint16 uFreq);
    uint16 getFreq(uint32 uniqueID);

	/// @brief ���֮ǰ�ļ�¼
	/// @return void
	/// @param peerID ���ӱ�ʾ��������Socket��ֵ���߼��ϵ�Peer�ȣ�
	void clearStat(uint64 peerID);

	/// @brief �жϲ���¼���յ�����Ϣ
	/// @return bool Ϊtrue��ʾ��Ч
	/// @param uniqueID ��Ϣ�ı�ţ������ڲ���ʹ��ϵͳ�ĵ�ǰʱ�䣩
	bool isValid(uint64 peerID, uint32 uniqueID);

	/// @brief �жϲ���¼���յ�����Ϣ
	/// @return bool Ϊtrue��ʾ��Ч
	/// @param uniqueID ��Ϣ�ı��
	/// @param curTime ��ǰʱ�䣨��ĳЩ����£����ϲ㴫�룬���������Ч�ʣ�
	bool isValid(uint64 peerID, uint32 uniqueID, uint64 curTime);

private:
    BCLib::Utility::CHashMap<uint32, uint16> m_FreqMap;
	BCLib::Utility::CHashMap<uint64, CRecord*> m_StatMap;
};

}//Framework
}//BCLib


#endif//__BCLIB_FRAMEWORK_MSGFREQ_H__
