/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2018 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

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

#include "NFGuildRedisModule.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"
#include "NFComm/NFPluginModule/NFINetModule.h"

NFGuildRedisModule::NFGuildRedisModule(NFIPluginManager * p)
{
    pPluginManager = p;
}

bool NFGuildRedisModule::Init()
{
    return true;
}

bool NFGuildRedisModule::Shut()
{
    return true;
}

bool NFGuildRedisModule::Execute()
{
    return true;
}

bool NFGuildRedisModule::AfterInit()
{
    m_pLogicClassModule = pPluginManager->FindModule<NFIClassModule>();
    m_pNoSqlModule = pPluginManager->FindModule<NFINoSqlModule>();
    m_pCommonRedisModule = pPluginManager->FindModule<NFICommonRedisModule>();
    m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();

    return true;
}

bool NFGuildRedisModule::ExistGuild(const std::string & strName)
{
	return false;
}

bool NFGuildRedisModule::CreateGuild(const NFGUID & self, const std::string & strGuildName, const NFGUID & xCreater)
{
	return false;
}


