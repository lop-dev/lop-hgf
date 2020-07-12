//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/algorithm/variableGear.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_IO_VARIABLEGEAR_H__
#define __BCLIB_UTILITY_IO_VARIABLEGEAR_H__

#include <BCLib/utility/baseDef.h>
#include <BCLib/utility/hashMap.h>
#include <BCLib/utility/dateTime.h>

namespace BCLib
{
namespace Utility
{

//////////////////////////////////////////////////////////////////////////
/// @brief �����ٳ��֣�����ʱ�䵥λ�Ǻ���
//////////////////////////////////////////////////////////////////////////
class BCLIB_UTILITY_API CVariableGear
{
public:
	CVariableGear();
	virtual ~CVariableGear();

	/// @brief �����жϵļ�������
	/// @return void
	/// @param fPercentError ������С��60���Ӵ���10���ӵ���ֵ
	void setCycleTime(uint32 uCycleTime);
	uint32 getCycleTime(){return m_uCycleTime;}

	/// @brief ���������жϵİٷ����
	/// @return void
	/// @param fPercentError ������С��1����0.1����ֵ
	void setPercentError(float fPercentError);
	float getPercentError(){return m_fPercentError;}

	/// @brief �жϿͻ����Ƿ�ʹ���˱��ٳ���
	/// @return bool Ϊ false ʱ����ʾʹ���˱��ٳ���
	/// @param cltTime �ͻ��˴�������ʱ��
	bool isValid(uint64 cltTime);

	/// @brief �жϿͻ����Ƿ�ʹ���˱��ٳ���
	/// @return bool Ϊ false ʱ����ʾʹ���˱��ٳ���
	/// @param cltTime �ͻ��˴�������ʱ��
	/// @param srvTime �������Ի�ȡ��ʱ�䣨��ĳЩ����£����ϲ㴫�룬���������Ч�ʣ�
	bool isValid(uint64 cltTime, uint64 srvTime);

private:
	uint32 m_uCycleTime;   // �����жϵļ�������
	float m_fPercentError; // �����жϵİٷ����
	CHashMap<uint64, uint64> m_TimeMap; // <�ͻ���ʱ��, ������ʱ��>
};

}//Utility
}//BCLib


#endif//__BCLIB_UTILITY_IO_VARIABLEGEAR_H__
