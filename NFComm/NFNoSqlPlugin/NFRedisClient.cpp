/*
            This file is part of: 
                NoahFrame
            http://noahframe.com

   Copyright 2009 - 2018 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is opensorece software and you can redistribute it and/or modify
   it under the terms of the License.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "NFRedisClient.h"

NFRedisClient::NFRedisClient()
{
	mnPort = 0;
	bBusy = false;
	bAuthed = false;
    m_pRedisClientSocket = new NFRedisClientSocket();
}

bool NFRedisClient::Enable()
{
	return m_pRedisClientSocket->IsConnect();
}

bool NFRedisClient::Authed()
{
	return bAuthed;
}

bool NFRedisClient::Busy()
{
	return bBusy;
}

bool NFRedisClient::Connect(const std::string &ip, const int port, const std::string &auth)
{
    int64_t nFD = m_pRedisClientSocket->Connect(ip, port);
	if (nFD > 0)
	{
		mstrIP = ip;
		mnPort = port;
		mstrAuthKey = auth;

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

bool NFRedisClient::ReConnect()
{
	return m_pRedisClientSocket->ReConnect(mstrIP, mnPort);
}

bool NFRedisClient::IsConnect()
{
	if (m_pRedisClientSocket)
	{
		return m_pRedisClientSocket->IsConnect();
	}

	return false;
}

bool NFRedisClient::Execute()
{
    m_pRedisClientSocket->Execute();

    return false;
}

NF_SHARE_PTR<redisReply> NFRedisClient::BuildSendCmd(const NFRedisCommand& cmd)
{
	while (bBusy)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		//you can not use build send cmd funciton again if you are not using coroutine
		YieldFunction();
	}

	if (!IsConnect())
	{
		ReConnect();
		return nullptr;
	}
	else
	{
		std::string msg = cmd.Serialize();
		if (msg.empty())
		{
			return nullptr;
		}
		int nRet = m_pRedisClientSocket->Write(msg.data(), msg.length());
		if (nRet != 0)
		{
			return nullptr;
		}
	}
	
	bBusy = true;

	return ParseForReply();
}

NF_SHARE_PTR<redisReply> NFRedisClient::ParseForReply()
{
	struct redisReply* reply = nullptr;
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		// When the buffer is empty, reply will be null
		int ret = redisReaderGetReply(m_pRedisClientSocket->GetRedisReader(), (void**)&reply);
		if (ret == REDIS_OK && reply != nullptr)
		{
			break;
		}

		if (YieldFunction)
		{
			YieldFunction();
		}
		else
		{
			Execute();
		}

		if (!IsConnect())
		{
			ReConnect();
			break;
		}
	}

	bBusy = false;

	if (reply == nullptr)
	{
		return nullptr;
	}

	if (REDIS_REPLY_ERROR == reply->type)
	{
		// write log
		freeReplyObject(reply);
		return nullptr;
	}

	return NF_SHARE_PTR<redisReply>(reply, [](redisReply* r) { if (r) freeReplyObject(r); });
}

bool NFRedisClient::AUTH(const std::string& auth)
{
	NFRedisCommand cmd(GET_NAME(AUTH));
	cmd << auth;

	// if password error, redis will return REDIS_REPLY_ERROR
	// pReply will be null
	NF_SHARE_PTR<redisReply> pReply = BuildSendCmd(cmd);
	if (pReply == nullptr)
	{
		return false;
	}

	if (pReply->type == REDIS_REPLY_STATUS)
	{
		if (std::string("OK") == std::string(pReply->str, pReply->len) ||
			std::string("ok") == std::string(pReply->str, pReply->len))
		{
			bAuthed = true;
			return true;
		}
	}
	
	return false;
}