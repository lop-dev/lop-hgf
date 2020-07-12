//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/memory/memMalloc.h
//  author:     League of Perfect
/// @brief      �ڴ����(malloc/free),֧���Զ����ڴ���Դ,֧��crash�ָ�
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_MEMORY_MEMMALLOC_H__
#define __BCLIB_UTILITY_MEMORY_MEMMALLOC_H__

#include <BCLib/utility/function.h>

namespace BCLib
{
namespace Utility
{
//////////////////////////////////////////////////////////////////////////
/// @brief �ڴ����ģ��
//////////////////////////////////////////////////////////////////////////
class BCLIB_UTILITY_API CMemAlloc
{
public:
    /// @brief �����ⲿ�ڴ�ĺ���ԭ��
    /// @return void* �������ⲿ�ڴ��ַ,ʧ�ܷ���0;���ص��ⲿ�ڴ���ʼ��ַ����8�ֽڶ���,�ұ�����0����ڴ�!!!
    /// @param size �������ⲿ�ڴ��С
    typedef void* (*MEM_OPEN_FUN)(size_t size);
    /// @brief �ͷ��ⲿ�ڴ�ĺ���ԭ��
    /// @return void
    /// @param p �ͷŵ��ⲿ�ڴ��ַ
    typedef void(*MEM_CLOSE_FUN)(void* p);

    /// @brief ��ʼ���ڴ����ģ��
    /// @return size_t 0�ɹ�,��0ʧ��
    /// @param memOpen �����ⲿ�ڴ�ʹ�õ�ȫ�ֺ���ָ��/���Ա����ָ��/ָ�����
    /// @param memClose �ͷ��ⲿ�ڴ�ʹ�õ�ȫ�ֺ���ָ��/���Ա����ָ��/ָ�����
    /// @param memGranularity �ⲿ�ڴ�Ŀ�����,����Ϊ2����,��СΪ64k
    /// @param object ���Ա����ָ��������
    static size_t init(MEM_OPEN_FUN memOpen, MEM_CLOSE_FUN memClose, size_t memGranularity);
    static size_t init(const CFunction<void*, size_t>& memOpen, const CFunction<void, void*>& memClose, size_t memGranularity);
    template<class NAME>
    static size_t init(NAME* object, void*(NAME::* memOpen)(size_t), void(NAME::* memClose)(void*), size_t memGranularity)
    {
        return init(CFunctionObject<void*, NAME, size_t>(memOpen, object), CFunctionObject<void, NAME, void*>(memClose, object), memGranularity);
    }

    /// @brief ��ʼ���ڴ����ģ��,����crash��ָ�
    /// @return size_t 0�ɹ�,��0ʧ��
    /// @param memOpen �����ⲿ�ڴ�ʹ�õ�ȫ�ֺ���ָ��/���Ա����ָ��/ָ�����
    /// @param memClose �ͷ��ⲿ�ڴ�ʹ�õ�ȫ�ֺ���ָ��/���Ա����ָ��/ָ�����
    /// @param ppOldMem �ⲿ�ڴ�ľ���ʼ��ַ����(ֻ��Ҫ�ṩ����,init�ڲ��������ʼ��ַ)
    /// @param ppNewMem �ⲿ�ڴ������ʼ��ַ����
    /// @param pSize �ⲿ�ڴ�Ĵ�С����
    /// @param memCnt �ⲿ�ڴ�ĸ���
    /// @param object ���Ա����ָ��������
    static size_t init(MEM_OPEN_FUN memOpen, MEM_CLOSE_FUN memClose, void** ppOldMem, void** ppNewMem, size_t* pSize, size_t memCnt);
    static size_t init(const CFunction<void*, size_t>& memOpen, const CFunction<void, void*>& memClose, void** ppOldMem, void** ppNewMem, size_t* pSize, size_t memCnt);
    template<class NAME>
    static size_t init(NAME* object, void*(NAME::* memOpen)(size_t), void(NAME::* memClose)(void*), void** ppOldMem, void** ppNewMem, size_t* pSize, size_t memCnt)
    {
        return init(CFunctionObject<void*, NAME, size_t>(memOpen, object), CFunctionObject<void, NAME, void*>(memClose, object), ppOldMem, ppNewMem, pSize, memCnt);
    }

    /// @brief ����ʹ���ڴ����ģ��
    /// @return void
    /// @param clearMem true:�����ѷ�����ڴ�, false:������
    static void final(bool clearMem);

    /// @brief ����dummyָ��,crash�ָ����Կ�ȡ��,Ĭ��ֵΪ0
    /// @return void
    /// @param p dummyָ��
    static void setDummy(void* p);

    /// @brief ��ȡdummyָ��
    /// @return void* dummyָ��
    static void* getDummy();

    /// @brief ���ɵĵ�ַת��Ϊ�µĵ�ַ(crash��ʹ��)
    /// @return void* ת������µ�ַ,ʧ�ܷ���0
    /// @param p ��Ҫת���ĵ�ַ
    /// @param ppOldMem �ⲿ�ڴ�ľ���ʼ��ַ����(����init���ȡ)
    /// @param ppNewMem �ⲿ�ڴ������ʼ��ַ����
    /// @param pSize �ⲿ�ڴ�Ĵ�С����
    /// @param memCnt �ⲿ�ڴ�ĸ���
    static void* addrConvert(void* p, void** ppOldMem, void** ppNewMem, size_t* pSize, size_t memCnt);

    /// @brief �����ڴ��
    /// @return void* �����ڴ��ĵ�ַ,ʧ�ܷ���0
    /// @param n �ڴ���С,0��ʾ�ɷ������С�ڴ��(32λϵͳΪ16�ֽ�,64λϵͳΪ32�ֽ�)
    static void* malloc(size_t n);

    /// @brief �ͷ��ڴ��
    /// @return void
    /// @param p �ͷ��ڴ��ĵ�ַ,�����ַ�����ѷ����,�ᵼ���쳣�ж��˳�
    static void free(void* p);

    /// @brief �ⲿ�ڴ�ʹ����
    /// @return size_t �ⲿ�ڴ�ʹ����
    /// @param
    static size_t footprint(void);

    /// @brief �ⲿ�ڴ�ʹ�����ķ�ֵ
    /// @return size_t �ⲿ�ڴ�ʹ�����ķ�ֵ
    /// @param
    static size_t footprintMax(void);

    /// @brief �ⲿ�ڴ�ʹ����������
    /// @return size_t �ⲿ�ڴ�ʹ����������,Ĭ��Ϊsize_t���͵����ֵ
    /// @param
    static size_t footprintLimit(void);

    /// @brief �����ⲿ�ڴ�ʹ����������
    /// @return size_t ���ú���ⲿ�ڴ�ʹ����������
    /// @param bytes �ⲿ�ڴ�ʹ����������,���Զ����ⲿ�ڴ�Ŀ�����ȡ�Ͻ����
    static size_t setFootprintLimit(size_t bytes);
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_MEMORY_MEMMALLOC_H__
