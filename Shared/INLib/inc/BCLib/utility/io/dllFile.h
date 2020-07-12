//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/io/dllFile.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_IO_DLLFILE_H__
#define __BCLIB_UTILITY_IO_DLLFILE_H__

#include <BCLib/utility/baseDef.h>

namespace BCLib
{
namespace Utility
{
//////////////////////////////////////////////////////////////////////////
/// @brief �Զ�̬���ļ��Ĳ���
//////////////////////////////////////////////////////////////////////////
class BCLIB_UTILITY_API CDllFile
{
public:
    CDllFile();
    ~CDllFile();
    bool open(const char* dllFile);
    /// @brief ��ȡ������ַ
    /// @return void*
    /// @param funName
    void* getFun(const char* funName);
    void close();

private:
    //���ؽ����̵ĵ�ַ
    void* m_dllFile;
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_IO_DLLFILE_H__
