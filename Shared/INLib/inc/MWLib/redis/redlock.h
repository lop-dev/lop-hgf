/* RedLock implement DLM(Distributed Lock Manager) with cpp.
 *
 * Copyright (c) 2014, jacketzhong <jacketzhong at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __MWLIB_REDIS_REDLOCK_H__
#define __MWLIB_REDIS_REDLOCK_H__

#include <MWLib/redis/baseDef.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <hiredis.h>
#include <sds.h>

namespace MWLib
{
namespace Redis
{
class CRedisClient;
class MWLIB_REDIS_API CLock
{
public:
    CLock()
    {
        m_validityTime = 0;
        m_resource = NULL;
        m_val = NULL;
    }
    ~CLock()
    {
        sdsfree(m_resource);
        sdsfree(m_val);
    }
public:
    int                     m_validityTime; // ��ǰ�����Դ���ʱ��, ����
    sds                     m_resource;     // Ҫ��ס����Դ����
    sds                     m_val;          // ��ס��Դ�Ľ����������
};

class MWLIB_REDIS_API CRedLock
{
public:
    CRedLock();
    virtual                 ~CRedLock();

public:
    bool                    Initialize();
    bool                    AddServerContext(redisContext * c, BCLib::uint16 type, CRedisClient *pRedisClient);
    bool                    delServerContext(redisContext * c, BCLib::uint16 type);
    void                    SetRetry(const int count, const int delay);
    int                     Lock(const char *resource, const int ttl, CLock &lock, BCLib::uint16 type);
    bool                    ContinueLock(const char *resource, const int ttl, CLock &lock, BCLib::uint16 type);
    bool                    Unlock(const CLock &lock, BCLib::uint16 type);

private:
    int                     LockInstance(redisContext *c, const char *resource, const char *val, const int ttl);
    bool                    ContinueLockInstance(redisContext *c, const char *resource, const char *val, const int ttl);
    void                    UnlockInstance(redisContext *c, const char *resource, const char *val);
    sds                     GetUniqueLockId();
    redisReply *            RedisCommandArgv(redisContext *c, int argc, char **inargv);

private:
    int              m_defaultRetryCount;    // Ĭ�ϳ��Դ���3
    int              m_defaultRetryDelay;    // Ĭ�ϳ�����ʱ200����
    float            m_clockDriftFactor;     // ����ʱ�����0.01

private:
    sds                     m_unlockScript;         // �����ű�
    int                     m_retryCount;           // try count
    int                     m_retryDelay;           // try delay
    int                     m_quoRum;               // majority nums

	std::unordered_map<BCLib::uint16, redisContext *> m_redisServerMap;
    //std::vector<redisContext *>  m_redisServer;          // redis master servers
    CLock   m_continueLock;         // ����
    sds                     m_continueLockScript;   // �����ű�

	CRedisClient *m_pRedisClient;
};
}//Redis
}//MWLib
#endif // __MWLIB_REDIS_REDLOCK_H__
