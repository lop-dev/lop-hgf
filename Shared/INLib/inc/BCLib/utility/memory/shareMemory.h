//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/memory/shareMemory.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_MEMORY_SHAREMEMORY_H__
#define __BCLIB_UTILITY_MEMORY_SHAREMEMORY_H__

#include <BCLib/utility/baseDef.h>

namespace BCLib
{
namespace Utility
{
typedef BCLib::uint32 ShmKey;
typedef BCLib::uint32 ShmSize;

enum EShareMemoryError
{
    ESME_ERROR          = -1,
    ESME_SUCCESS        = 0,
    ESME_SUCCESS_EXISTS = 1,
};

class BCLIB_UTILITY_API CShareMemory
{
public:
    CShareMemory();
    ~CShareMemory();

    /// @brief ���������ڴ�
    /// @return int ���������ڴ淵��ֵ�� EShmErrorCode
    /// @param key �����ڴ�ʶ��ֵ
    /// @param size �����ڴ��С
    /// @param shareBuff ��������ɹ����Ѿ����ڣ����ع����ڴ��ַ
    EShareMemoryError create(ShmKey key, ShmSize size, void** shareBuff);
    void close();

    ShmKey getKey() const
    {
        return m_key;
    }
    ShmSize getSize() const
    {
        return m_size;
    }
    void* getSharedMemory() const
    {
        return m_pShm;
    }

private:
    ShmKey m_key;
    ShmSize m_size;
    void* m_pShm;

#if defined(_WIN32)

    HANDLE m_handle;

#elif defined(_LINUX)

    int32 m_handle;

#endif
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_MEMORY_SHAREMEMORY_H__
