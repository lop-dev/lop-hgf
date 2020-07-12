//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/security/security.h
//  author:     League of Perfect
/// @brief      ����/����/��ϣ
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_SECURITY_SECURITY_H__
#define __BCLIB_SECURITY_SECURITY_H__

#include <BCLib/security/baseDef.h>

namespace BCLib
{
namespace Security
{
enum ESecurityError
{
    ESE_OK,
    ESE_NOT_INIT,               //δ��ʼ����������Ҫ��Կ���㷨δ������Կ
    ESE_INVALID_KEY,            //��Կ����
    ESE_INVALID_KEYLEN,         //��Կ���ȴ���
    ESE_INVALID_INPUT,          //�Ƿ����룬�����ָ�������Ҫ���ܵĳ���Ϊ0
    ESE_INVALID_OUTPUT,         //�Ƿ����
    ESE_NOT_ENOUGH_BUFFER,      //�������̫С
    ESE_CANNOT_DECODE,          //�ǶԳ��㷨���޷�����
    ESE_CANNOT_HASH,            //��֧�ֵĹ�ϣ�㷨
    ESE_CANNOT_OPEN_FILE,       //�޷��������ļ�
    ESE_UNKNOWN_FILE_ERROR,     //δ֪�ļ�����ʧ��
};

//////////////////////////////////////////////////////////////////////////
/// @brief ͳһ�ӿ�
//////////////////////////////////////////////////////////////////////////
class BCLIB_SECURITY_API CSecurity
{
public:
    /// @brief ��ʼ��
    /// @return ESecurityError
    virtual ESecurityError init() = 0;

    /// @brief ������Կ
    /// @return ESecurityError
    /// @param key ��Կ
    /// @param len ��Կ����
    virtual ESecurityError setKey(const char* key, uint32 len) = 0;

    /// @brief ����/��ϣ
    /// @return ESecurityError
    /// @param src ��Ҫ���ܵ�����
    /// @param srclen ��Ҫ���ܵĳ���
    /// @param dst ���ܺ������
    /// @param dstlen ���ܺ�ĳ���
    virtual ESecurityError encode(const char* src, uint32 srclen, char* dst, uint32& dstlen) = 0;

    /// @brief ����
    /// @return ESecurityError
    /// @param src ��Ҫ���ܵ�����
    /// @param srclen ��Ҫ���ܵĳ���
    /// @param dst ���ܺ������
    /// @param dstlen ���ܺ�ĳ���
    virtual ESecurityError decode(const char* src, uint32 srclen, char* dst, uint32& dstlen) = 0;

    virtual ~CSecurity()
    {
    }
};

enum ESecurityType
{
    EST_MD5,
    EST_SHA1,
    EST_RC4,
    EST_AES,
    EST_TOTAL
};

/// @brief ����CSecurity����
/// @return CSecurity*
/// @param stype CSecurity��������
BCLIB_SECURITY_API CSecurity* createSecurity(ESecurityType stype);

/// @brief ����CSecurity����
/// @return void
/// @param stype CSecurity*
BCLIB_SECURITY_API void destroySecurity(CSecurity* pSecurity);

/// @brief ���ļ���ϣ������������浽�ڴ�
/// @return ESecurityError
/// @param stype ��ϣ�㷨
/// @param path ��Ҫ��ϣ���ļ�·��
/// @param dst ���������ڴ�
/// @param dstlen ���������ڴ�ĳ���
BCLIB_SECURITY_API ESecurityError hashFile(ESecurityType stype, const char* path, char* dst, uint32& dstlen);
}//Security
}//BCLib

#endif//__BCLIB_SECURITY_SECURITY_H__
