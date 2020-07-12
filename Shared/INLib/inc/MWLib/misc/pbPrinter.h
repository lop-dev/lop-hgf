//////////////////////////////////////////////////////////////////////
//  created:    2016/06/05
//  filename:   MWLib/misc/pbPrinter.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __MWLIB_MISC_PBPRINTER_H__
#define __MWLIB_MISC_PBPRINTER_H__

#include <BCLib/utility/singleton.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/descriptor.pb.h>
#include <sstream>

namespace MWLib
{
    namespace Misc
    {
        class CPBPrinter
        {
            BCLIB_SINGLETON_DECLARE(CPBPrinter);

        protected:
            CPBPrinter();
            virtual ~CPBPrinter();

        private:
            void _printMessages(std::ostream& os, const google::protobuf::Message &Message_P, const google::protobuf::Descriptor *pDescriptor, const google::protobuf::Reflection *pReflection, int deepnum, bool format = true);

        public:
            /**
            * ��һ�� protobuf���л���json��
            * @param os           ������ַ���������
            * @param root_message ��Ҫת������Ϣ
            */
            void printJsonByIO(std::ostream& os, const google::protobuf::Message &root_message, bool format = true)
            {
                const google::protobuf::Reflection *pReflection = root_message.GetReflection();
                const google::protobuf::Descriptor *pDescriptor = root_message.GetDescriptor();
                _printMessages(os, root_message, pDescriptor, pReflection, 1, format);
            }

            //���̰߳�ȫ����
            //google::protobuf::streambuf* getJsonStream(const google::protobuf::Message &root_message, bool format = false)
            //{
            //    m_strm.str("");	//�п�ʱ�о�һ������ڴ�᲻��仯
            //    m_strm.clear();
            //    const google::protobuf::Reflection *pReflection = root_message.GetReflection();
            //    const google::protobuf::Descriptor *pDescriptor = root_message.GetDescriptor();
            //    _printMessages(m_strm, root_message, pDescriptor, pReflection, 1, format);
            //    return m_strm.rdbuf();
            //}

            //���߳̿���
            std::string getJsonStream(const google::protobuf::Message &root_message, bool format = false)
            {
                std::stringstream strm;
                strm.str("");	//�п�ʱ�о�һ������ڴ�᲻��仯-->>�����ڴ��Сû�б仯
                strm.clear();
                const google::protobuf::Reflection *pReflection = root_message.GetReflection();
                const google::protobuf::Descriptor *pDescriptor = root_message.GetDescriptor();
                _printMessages(strm, root_message, pDescriptor, pReflection, 1, format);
                return strm.str();
            }

        private:
            std::stringstream m_strm;
        };
    }//Utility
}//MWLib

#endif//__MWLIB_MISC_PBPRINTER_H__
