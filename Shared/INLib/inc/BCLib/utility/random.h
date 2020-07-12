//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/random.h
//  author:     League of Perfect
/// @brief      ���������
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_RANDOM_H__
#define __BCLIB_UTILITY_RANDOM_H__

#include <BCLib/utility/baseDef.h>

namespace BCLib
{
namespace Utility
{
//////////////////////////////////////////////////////////////////////////
/// @brief �����
//////////////////////////////////////////////////////////////////////////
class BCLIB_UTILITY_API CRandom
{
public:
    /// @brief ��������캯��
    /// @return
    /// @param iSeed �������
    CRandom(unsigned int iSeed);
    virtual ~CRandom() ;

    /// @brief���[0,2^32]
    /// @return unsigned int
    unsigned int rand32Bits();
    /// @brief ���� [iMin,iMax]����������
    /// @return unsigned int
    /// @param iMin
    /// @param iMax
    unsigned int randInt(unsigned int iMin, unsigned int iMax);

private:
    unsigned int _rand15Bits();
    unsigned int m_iSeed;
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_RANDOM_H__
