//
// Author: LUSHENG HUANG Created on 17/11/17.
//

#include "NFRedisClient.h"

NFRedisClient::NFRedisClient()
{
	mnIndex = 0;
    m_pRedisClientSocket = new NFRedisClientSocket();
}


bool NFRedisClient::ConnectTo(const std::string &ip, const int port, const std::string &auth)
{
    int64_t nFD = m_pRedisClientSocket->Connect(ip, port);
	if (nFD > 0)
	{
		if (!auth.empty())
		{
			return AUTH(auth);
		}

		return true;
	}

    return false;
}

bool NFRedisClient::SelectDB(int dbnum)
{
    return false;
}

bool NFRedisClient::KeepLive()
{
    return false;
}

bool NFRedisClient::Execute()
{
    m_pRedisClientSocket->Execute();

    return false;
}

int64_t NFRedisClient::BuildSendCmd(const NFRedisCommand& cmd)
{
	std::string msg = cmd.Serialize();
	int nRet = m_pRedisClientSocket->Write(msg.data(), msg.length());
	if (nRet != 0)
	{
		//lost net
		//do some thing
		return 0;
	}

	mnIndex++;

	int64_t index = mnIndex;
	mnIndexList.push_back(index);

	void* reply = nullptr;
	while (true)
	{
		//get reply
		const int nFrontIndex = mnIndexList.front();
		if (nFrontIndex == index)
		{
			int ret = redisReaderGetReply(m_pRedisClientSocket, &reply);
			if (ret == REDIS_OK)
			{
				break;
			}
			else
			{
				if (YieldFunction)
				{
					YieldFunction();
				}
				else
				{
					Execute();
				}
			}
		}

		continue;
	}

	if (reply == nullptr)
	{
		printf("redisReply is NULL!\n");
		return 0;
	}

	struct redisReply* r = (struct redisReply*)reply;
	if (REDIS_REPLY_ERROR == r->type)
	{
		printf("redisReply return REDIS_REPLY_ERROR!\n");
		freeReplyObject(reply);
		//redisReaderFree(reader);
		//reader = NULL;
		return 0;
	}

	if (REDIS_REPLY_STATUS != r->type)
	{
		printf("redisReply return is't REDIS_REPLY_STATUS!\n");
		freeReplyObject(reply);
		//redisReaderFree(reader);
		//reader = NULL;
		return 0;
	}

	return mnIndex;
}

bool NFRedisClient::AUTH(const std::string & auth)
{
	NFRedisCommand cmd(GET_NAME(AUTH));
	cmd << auth;

	NF_SHARE_PTR<NFRedisResult> pRedisResult = BuildSendCmd(cmd);
	
	WaitingResult(pRedisResult);

	return pRedisResult->IsOKRespStatus();
}