//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/exception.h
//  author:     League of Perfect
/// @brief      CException �쳣�׳�����
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_EXCEPTION_H__
#define __BCLIB_UTILITY_EXCEPTION_H__

#include <BCLib/utility/string.h>

namespace BCLib
{
namespace Utility
{
class BCLIB_UTILITY_API CException
{
public:
    /// @brief    CException ���캯��
    /// @param major �쳣��ID
    /// @param minor �쳣��ID
    /// @param errorMsg �쳣ע��
    /// @param osError ͨ��GetLastError/errno��ȡ��ϵͳ�쳣ID���� osError = -1 ʱ���Զ���ȡ.
    CException(int16 major, int16 minor, const CStringA& errorMsg = "Unknown error", int osError = 0);
    CException(const CException& e);
    virtual ~CException();

    CException& operator =(CException& e);

    const CStringA& getErrorStr() const
    {
        return m_errorMsg;
    }
    uint32 getErrorCode() const
    {
        return BCLIB_HI_SHIFT(m_major, 16) + m_minor;
    }

    /// @brief    �����쳣
    /// @param major �쳣��ID
    /// @param minor �쳣��ID
    /// @param errorMsg �쳣ע��
    /// @param osError ͨ��GetLastError/errno��ȡ��ϵͳ�쳣ID���� osError = -1 ʱ���Զ���ȡ.
    void setError(int16 major, int16 minor, const CStringA& errorMsg = "Unknown error", int osError = 0);

public:
    static void throwRruntimeError(const std::string strError);

    /// @brief    �����쳣
    /// @param major �쳣��ID
    /// @param minor �쳣��ID
    /// @param errorMsg �쳣ע��
    /// @param osError ͨ��GetLastError/errno��ȡ��ϵͳ�쳣ID���� osError = -1 ʱ���Զ���ȡ.
    static void setException(int16 major, int16 minor, const CStringA& errorMsg = "Unknown error", int osError = 0);
    static void setException(CException* err);
    static CException& getException();
    static void clearException();

private:
    uint16 m_major;
    uint16 m_minor;
    uint32 m_osErrno;
    CStringA m_errorMsg;
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_EXCEPTION_H__
