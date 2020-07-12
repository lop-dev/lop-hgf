//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/io/directoryInfo.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_IO_DIRECTORYINFO_H__
#define __BCLIB_UTILITY_IO_DIRECTORYINFO_H__

#include <BCLib/utility/baseDef.h>

namespace BCLib
{
namespace Utility
{
class BCLIB_UTILITY_API CDirectoryInfo
{
public:
    CDirectoryInfo(const std::string& dir = "");
    virtual ~CDirectoryInfo();

    void standardization();
    bool isExist();
    int makeDir();
    int getDirectories(std::vector<std::string>& ret);
    int getFiles(std::vector<std::string>& ret);

public:
    /// @brief Ŀ¼��׼��,��'\\'ͳһת����'/'
    /// @return void
    /// @param dir
    static void standardization(std::string& dir);

    /// @brief �ж�Ŀ¼�Ƿ����
    /// @return bool
    /// @param dir
    static bool isExist(const std::string& dir);

    /// @brief ����Ŀ¼
    /// @return int ,����ʧ�ܷ��� -1�������ɹ����� 0���Ѿ����ڷ��� 1
    /// @param dir
    static int makeDir(const std::string& dir);

    /// @brief ��ȡdirĿ¼��������Ŀ¼
    /// @return int
    /// @param dir
    /// @param ret
    static int getDirectories(const std::string& dir, std::vector<std::string>& ret);

    /// @brief ��ȡdirĿ¼�������ļ�
    /// @return int
    /// @param dir
    /// @param ret
    static int getFiles(const std::string& dir, std::vector<std::string>& ret);

    /// @brief ɾ��dirĿ¼�������ļ�
    /// @return int
    /// @param dir
    static int delFiles(const std::string& dir);

    /// @brief ���õ�ǰĿ¼
    /// @return bool
    /// @param dir
    static bool setCurDirectory(const std::string& dir);

    /// @brief ��ȡ��ǰĿ¼
    /// @return std::string
    static std::string getCurDirectory();

    /// @brief ��ȡ��ǰ��ִ�г����Ŀ¼
    /// @return std::string
    static std::string getExeDirectory();

private:
    std::string m_dirName;
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_IO_DIRECTORYINFO_H__
