//////////////////////////////////////////////////////////////////////
//  created:    2018/10/29
//  filename:   MWLib/kafka/producer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __MWLIB_KAFKA_PRODUCER_H__
#define __MWLIB_KAFKA_PRODUCER_H__

#include <BCLib/utility/noncopyable.h>
#include "kafka.h"

namespace qbus
{
    class QbusProducer;
}

namespace MWLib
{
namespace Kafka
{
typedef void(*ProduceCallback)(const char* msg, const size_t len, const char* key, const size_t key_len);

/************************************************************************/
/*   ������	�û�ʹ�������ߵ� produce �ӿڣ� ������д��kafka             */
/************************************************************************/
class MWLIB_KAFKA_API CKafkaProducer : public BCLib::Utility::CNoncopyable
{
public:
    CKafkaProducer();
    virtual ~CKafkaProducer();

    bool init(const char* configXmlPath);

    //��������
    bool produce(const char* msg, size_t len, const std::string&key);

    //��������ʧ��ʱ�Ļص�
    void setProduceCallback(ProduceCallback cb);

    void close();

private:
    qbus::QbusProducer *m_producer;
};
}//Kafka
}//MWLib

#endif//__MWLIB_KAFKA_PRODUCER_H__
