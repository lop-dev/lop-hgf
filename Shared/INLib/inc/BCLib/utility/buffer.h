//////////////////////////////////////////////////////////////////////
//  created:    2011/11/01
//  filename:   BCLib/utility/buffer.h
//  author:     League of Perfect
/// @brief
///
//////////////////////////////////////////////////////////////////////
#ifndef __BCLIB_UTILITY_BUFFER_H__
#define __BCLIB_UTILITY_BUFFER_H__

#include <BCLib/utility/baseDef.h>

namespace BCLib
{
namespace Utility
{
//////////////////////////////////////////////////////////////////////////
/// @brief ������������֧�� typedef CBuffer< std::vector<char>, char> CBufferInt8;
///  ���Ҫ֧���������͵Ļ���������Ҫ����ʵ��init��writeReserve
//////////////////////////////////////////////////////////////////////////
template<typename BUFFTYPE, typename ITEMTYPE = unsigned char>
class CBuffer
{
public:
    CBuffer()
    :m_bufferMaxSize(0)
    ,m_readPosition(0)
    ,m_writePosition(0)
    {
        init();
    }

    virtual ~CBuffer()
    {
    }

    /// @brief ��ʼ��
    /// @return void
    inline void init();

    /// @brief ����ռ�
    /// @return bool
    /// @param size
    inline bool writeReserve(uint32 size);

    /// @brief д������
    /// @return bool д���Ƿ�ɹ�
    /// @param data ��д������
    /// @param size
    bool push(const ITEMTYPE* data, uint32 size)
    {
        if(data == NULL || size == 0)
        {
            return true;
        }
        if(size < 0)
        {
            return false;
        }
        if(!writeReserve(size))
        {
            return false;
        }
        memcpy(&m_buffer[m_writePosition], data, size);
        writeFlip(size);
        return true;
    }

    /// @brief �������еĿɶ�������
    /// @return BCLib::uint32 ʵ�ʶ�ȡ�ĳ���
    /// @param buff ��������������������
    /// @param buffSize ׼����ȡ�ĳ���
    uint32 pop(ITEMTYPE* buff, uint32 buffSize)
    {
        if(buff == NULL)
        {
            return 0;
        }
        uint32 size = readSize();
        if(size <= 0)
        {
            return 0;
        }
        if(buffSize < size)
        {
            size = buffSize;
        }
        memcpy(buff, &m_buffer[m_readPosition], size);
        readFlip(size);
        return size;
    }

    /// @brief ��д��ַ
    /// @return ITEMTYPE*
    ITEMTYPE* writePtr()
    {
        uint32 tmp = m_writePosition - m_readPosition;
        if(m_readPosition >= tmp)
        {
            memmove(&m_buffer[0], &m_buffer[m_readPosition], tmp);
            m_readPosition = 0;
            m_writePosition = tmp;
        }

        return &m_buffer[m_writePosition];
    }

    /// @brief �ɶ���ַ
    /// @return const ITEMTYPE*
    const ITEMTYPE* readPtr() const
    {
        return &m_buffer[m_readPosition];
    }

    /// @brief �Ƿ�ɶ�
    /// @return bool
    bool readReady() const
    {
        return m_writePosition - m_readPosition > 0;
    }

    /// @brief �ɶ��ռ��С
    /// @return BCLib::uint32
    uint32 readSize() const
    {
        return m_writePosition - m_readPosition;
    }

    /// @brief ��д�ռ��С
    /// @return BCLib::uint32
    uint32 writeSize() const
    {
        return m_bufferMaxSize - m_writePosition;
    }

    void reset()
    {
        m_readPosition = 0;
        m_writePosition = 0;
    }

    /// @brief �ڲ�����,��overlap�����д���
    /// @return void
    /// @param size
    void readFlip(uint32 size)
    {
        m_readPosition += size;
        if(m_readPosition >= m_writePosition)
        {
            m_readPosition = 0;
            m_writePosition = 0;
        }
    }

    bool writeFlip(uint32 size)
    {
        if(m_writePosition + size > m_bufferMaxSize)
        {
            return false;
        }
        m_writePosition += size;

        uint32 tmp = m_writePosition - m_readPosition;
        if(m_readPosition >= tmp)
        {
            memmove(&m_buffer[0], &m_buffer[m_readPosition], tmp);
            m_readPosition = 0;
            m_writePosition = tmp;
        }

        return true;
    }

    uint32 getBuffMaxSize()
    {
        return m_bufferMaxSize;
    }
    uint32 getReadPosition()
    {
        return m_readPosition;
    }
    uint32 getWritePosition()
    {
        return m_writePosition;
    }

protected:
private:
    //��������ǰ��С
    uint32 m_bufferMaxSize;
    uint32 m_readPosition;
    uint32 m_writePosition;
    BUFFTYPE m_buffer;
};
}//Utility
}//BCLib

#endif//__BCLIB_UTILITY_BUFFER_H__
