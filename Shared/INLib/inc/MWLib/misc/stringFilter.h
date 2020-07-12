//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   MWLib/misc/stringFilter.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __MWLIB_MISC_STRINGFILTER_H__
#define __MWLIB_MISC_STRINGFILTER_H__

#include <MWLib/misc/miscDef.h>


namespace MWLib
{
namespace Misc
{
//! StringFilter����С��ģ�����ؼ��ֵ�����
class MWLIB_MISC_API CStringFilter
{
public:
    CStringFilter();
    virtual ~CStringFilter();

    void setMark(char cMark);

    void addUnLawKeyWordInUTF8(const std::string& kUTF8Word);                                             //! kUTF8WordΪUTF8��ʽ
    void addUnLawKeyWordInANSI(const std::string& kANSIWord);                                             //! kANSIWordΪANSI��ʽ
    void addUnLawKeyWordsInUTF8(const std::string& kUTF8WordsStream);                                     //! kUTF8WordsStreamΪUTF8��ʽ,\n����,һ��һ���ؼ���
    void addUnLawKeyWordsInANSI(const std::string& kANSIWordsStream);                                     //! kANSIWordsStreamΪANSI��ʽ,\n����,һ��һ���ؼ���

    bool hasUnLawKeyWordInUTF8(const std::string& kUTF8Str) const;                                        //! kUTF8StrΪUTF-8��ʽ
    bool checkAndReplaceUnLawKeyWordsInUTF8(const std::string& kUTF8Src, std::string& kUTF8Des) const;    //! kUTF8Src,kUTF8DesΪUTF-8��ʽ

protected:
    struct SUnLawKeyWord
    {
        std::string m_unLawKeyWord;
        std::string m_markWord;

        SUnLawKeyWord(const std::string& unLawKeyWord, const std::string& markWord);
    };
    typedef std::vector<SUnLawKeyWord> UnLawKeyWords;
    UnLawKeyWords m_kUnLawKeyWords;
    char m_cMark;
};


//! FvMassStringFilter���ڴ��ģ�����ؼ��ֵ�����
class MWLIB_MISC_API CMassStringFilter
{
public:
    CMassStringFilter();
    ~CMassStringFilter();

    void setMark(char cMark);

    void addUnLawKeyWordsInUTF8(const std::string& kUTF8WordsStream);                                     //! kUTF8WordsStreamΪUTF8��ʽ,\n����,һ��һ���ؼ���
    void addUnLawKeyWordsInANSI(const std::string& kANSIWordsStream);                                     //! kANSIWordsStreamΪANSI��ʽ,\n����,һ��һ���ؼ���

    bool hasUnLawKeyWordInUTF8(const std::string& kUTF8Str) const;                                        //! kUTF8StrΪUTF-8��ʽ
    bool checkAndReplaceUnLawKeyWordsInUTF8(const std::string& kUTF8Src, std::string& kUTF8Des) const;    //! kUTF8Src,kUTF8DesΪUTF-8��ʽ

protected:
    struct SUnLawKeyWord
    {
        std::string m_unLawKeyWord;
        std::string m_markWord;

        SUnLawKeyWord(const std::string& unLawKeyWord, const std::string& markWord);
    };
    typedef std::vector<SUnLawKeyWord> UnLawKeyWords;
    UnLawKeyWords* _findKeyWords(BCLib::uint64 uiWord) const;
    typedef std::map<BCLib::uint64, UnLawKeyWords*> UnLawKeyWordMap;
    void _addUnLawKeyWordInUTF8(const std::string& kUTF8Word, UnLawKeyWordMap& kMap);
    void _addUnLawKeyWordInANSI(const std::string& kANSIWord, UnLawKeyWordMap& kMap);

protected:
    typedef std::pair<BCLib::uint64, UnLawKeyWords*> UnLawKeyWordsPair;
    BCLib::uint32 m_uiUnLawKeyWordsPairArraySize;
    UnLawKeyWordsPair* m_pkUnLawKeyWordsPairArray;
    char m_cMark;
};


void MWLIB_MISC_API ANSI_To_UTF8(std::string& kStr);
void MWLIB_MISC_API UTF8_To_ANSI(std::string& kStr);
void MWLIB_MISC_API ANSI_To_UTF16(const std::string& kSrc, std::wstring& kDes);
void MWLIB_MISC_API UTF16_To_ANSI(const std::wstring& kSrc, std::string& kDes);
void MWLIB_MISC_API UTF8_To_UTF16(const std::string& kSrc, std::wstring& kDes);
void MWLIB_MISC_API UTF16_To_UTF8(const std::wstring& kSrc, std::string& kDes);

//! ȡ����һ��UTF8����
size_t MWLIB_MISC_API getUTF8Word(const char* pcUTF8Str, size_t uiOffset, BCLib::uint64& kUTF8Word);

//! �ж�һ���ַ��Ƿ�Ϊ�հ��ַ���
bool MWLIB_MISC_API isBlankString(const char* str);


//! ͳ���ַ����е�"����"
//! kStr: UTF8��ʽ�ַ���
//! iAsciiCoef: Ascii�ַ������"����"
//! iNotAsciiCoef: ��Ascii�ַ������"����"
int MWLIB_MISC_API calcWordCnt(const std::string& kUTF8Str, int iAsciiCoef=1, int iNotAsciiCoef=1);

BCLib::uint16 MWLIB_MISC_API UTF8_TO_UNICODE(const char* pcUTF8Str, wchar_t* pwcUnicodeStr, BCLib::uint8 uiUnicodeLen);


namespace StrFilterTest
{
/**
    static void Test()
    {
        //! ͳ���ַ����е�"����"
        {
            std::string kANSIStr("KMP�������ǹ�����DFA��������ģ�⣬");
            //! �ַ�������ΪUTF8��ʽ,ת��UTF8��ʽ
            ANSI_To_UTF8(kANSIStr);
            //! ͳ���ַ����е�"����",ANSI�ַ���1��,��ANSI�ַ���2��
            int iCnt = calcWordCnt(kANSIStr, 1, 2);
            printf("word cnt : %d\n", iCnt);
        }

        //! �����ּ��
        {
            CStringFilter kFilter;

            //! ����������,�����ε�����ʾ'#'
            kFilter.setMark('#');

            //! ���������"ABC",ANSI��ʽ
            kFilter.addUnLawKeyWordInANSI("ABC");

            //! ����������б�
            //! ���ļ�test.csv�ж�ȡ,һ��һ��������,ANSI��ʽ
            //! test.csv������:
            //! DDD
            //! FFF
            {
                FILE* pkFile = fopen("test.csv", "rt");
                if(!pkFile)
                {
                    return;
                }
                fseek(pkFile, 0, SEEK_END);
                size_t uiFileSize = ftell(pkFile);
                char* pkBuf = new char[uiFileSize];
                fseek(pkFile, 0, SEEK_SET);
                fread(pkBuf, uiFileSize, 1, pkFile);
                fclose(pkFile);

                kFilter.addUnLawKeyWordsInANSI(pkBuf);
            }

            //! ����ַ������Ƿ���������
            std::string kANSIStr("AAABC����DDFFFDDE");
            //! �ַ�������ΪUTF8��ʽ,ת��UTF8��ʽ
            ANSI_To_UTF8(kANSIStr);
            if(kFilter.hasUnLawKeyWordInUTF8(kANSIStr))
            {
                //! ����������
                UTF8_To_ANSI(kANSIStr);
                printf("%s\n", kANSIStr.c_str());
            }

            //! ��鲢���������滻������
            ANSI_To_UTF8(kANSIStr);
            std::string kUTF8DesStr;
            if(kFilter.checkAndReplaceUnLawKeyWordsInUTF8(kANSIStr, kUTF8DesStr))
            {
                //! ����������
                UTF8_To_ANSI(kUTF8DesStr);
                printf("%s\n", kUTF8DesStr.c_str());
            }
        }
    }
**/
}//StrFilterTest
}//Misc
}//MWLib

#endif//__MWLIB_MISC_STRINGFILTER_H__
