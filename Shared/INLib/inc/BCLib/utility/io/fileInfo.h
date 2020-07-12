//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/io/fileInfo.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_IO_FILEINFO_H__
#define __BCLIB_UTILITY_IO_FILEINFO_H__

#include <BCLib/utility/baseDef.h>
#include <BCLib/utility/dateTime.h>

namespace BCLib
{
namespace Utility
{
class BCLIB_UTILITY_API CFileInfo
{
public:
    CFileInfo(const std::string& fileName = "");
    virtual ~CFileInfo(void);

public:
    void standardization();
    bool isExist();
    std::string getFullPath();
    std::string getPath();
    std::string getFullName();
    std::string getName();
    std::string getExtension();
    int64 getLength();
    bool isReadOnly();
    bool copyFile(const std::string& dst);
    bool deleteFile();

public:
    /// @brief Ŀ¼��׼������window�����н�'/'ת���ɡ�\\����linu�����н�'\\'ת����'/'
    /// @return void
    /// @param fileName
    static void standardization(std::string& fileName);

    /// @brief �ж��ļ��Ƿ����
    /// @return bool
    /// @param fileName
    static bool isExist(const std::string& fileName);

    /// @brief ��ȡ�ļ�������Ŀ¼
    /// @return std::string
    /// @param fileName
    static std::string getFullPath(const std::string& fileName);

    /// @brief ��ȡ�ļ����ڵ�Ŀ¼
    /// @return std::string
    /// @param fileName
    static std::string getPath(const std::string& fileName);

    /// @brief ��ȡ�����ļ��� �ļ���+��չ��
    /// @return std::string
    /// @param fileName
    static std::string getFullName(const std::string& fileName);

    /// @brief ��ȡ�ļ�����������չ��
    /// @return std::string
    /// @param fileName
    static std::string getName(const std::string& fileName);

    /// @brief ��ȡ�ļ���չ��
    /// @return std::string
    /// @param fileName
    static std::string getExtension(const std::string& fileName);

    /// @brief ��ȡ�ļ�����
    /// @return unsigned int
    /// @param fileName
    static int64 getLength(const std::string& fileName);

    /// @brief �ж��ļ��Ƿ���ֻ������
    /// @return bool
    /// @param fileName
    static bool isReadOnly(const std::string& fileName);

    /// @brief �����ļ�
    /// @return bool
    /// @param dst
    /// @param src
    static bool copyFile(const std::string& dst, const std::string& src);

    /// @brief �������ļ�
    /// @return bool
    /// @param dst
    /// @param src
    static bool renameFile(const std::string& dst, const std::string& src);

    /// @brief ɾ���ļ�
    /// @return bool
    /// @param fileName
    static bool deleteFile(const std::string& fileName);

    /// @brief ��ȡ�ļ�ʱ��
    /// @return bool
    /// @param fileName
    /// @param pFileCreateTime      : win32: create time,       linux: change time (permissions, etc)
    /// @param pFileLastAccessTime  : win32: last access time,  linux: last access time
    /// @param pFileLastWriteTime   : win32: last write tiem,   linux: last modify time
    static bool getFileTime(const std::string& filename, CDateTime* pFileCreatTime, CDateTime* pFileLastAccessTime, CDateTime* pFileLastWriteTime);

private:
    std::string m_fileName;
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_IO_FILEINFO_H__
