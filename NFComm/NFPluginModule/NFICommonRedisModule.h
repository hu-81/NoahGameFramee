/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2020 NoahFrame(NoahGameFrame)

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

#ifndef NFI_COMMON_REDIS_MODULE_H
#define NFI_COMMON_REDIS_MODULE_H

#include "NFIModule.h"

class NFICommonRedisModule
    : public NFIModule
{
public:
	virtual std::string GetPropertyCacheKey(const NFGUID& self) = 0;
	virtual std::string GetRecordCacheKey(const NFGUID& self) = 0;
	virtual std::string GetFriendCacheKey(const NFGUID& self) = 0;
	virtual std::string GetFriendInviteCacheKey(const NFGUID& self) = 0;
	virtual std::string GetBlockCacheKey(const NFGUID& self) = 0;

	virtual std::string GetTeamCacheKey(const NFGUID& self) = 0;
	virtual std::string GetTeamInviteCacheKey(const NFGUID& self) = 0;

	virtual std::string GetAccountCacheKey(const std::string& account) = 0;
	virtual std::string GetTileCacheKey(const int& sceneID) = 0;
	virtual std::string GetSceneCacheKey(const int& sceneID) = 0;
	virtual std::string GetCellCacheKey(const std::string& strCellID) = 0;

	virtual NF_SHARE_PTR<NFIPropertyManager> NewPropertyManager(const std::string& className) = 0;
	virtual NF_SHARE_PTR<NFIRecordManager> NewRecordManager(const std::string& className) = 0;

	virtual NF_SHARE_PTR<NFIPropertyManager> GetPropertyInfo(const NFGUID& self, const std::string& className, NF_SHARE_PTR<NFIPropertyManager> propertyManager = nullptr) = 0;
	virtual NF_SHARE_PTR<NFIRecordManager> GetRecordInfo(const NFGUID& self, const std::string& className, NF_SHARE_PTR<NFIRecordManager> recordManager = nullptr) = 0;

	virtual bool SavePropertyInfo(const NFGUID& self, const std::string& propertyName, const std::string& propertyValue) = 0;
	virtual bool SavePropertyInfo(const NFGUID& self, NF_SHARE_PTR<NFIPropertyManager> pPropertyManager, const int nExpireSecond = -1) = 0;
	virtual bool SaveRecordInfo(const NFGUID& self, NF_SHARE_PTR<NFIRecordManager> pRecordManager, const int nExpireSecond = -1) = 0;


	virtual bool GetPropertyList(const NFGUID& self, const std::vector<std::string>& fields, std::vector<std::string>& values) = 0;

	virtual NFINT64 GetPropertyInt(const NFGUID& self, const std::string& propertyName) = 0;
	virtual int GetPropertyInt32(const NFGUID& self, const std::string& propertyName) = 0;
	virtual double GetPropertyFloat(const NFGUID& self, const std::string& propertyName) = 0;
	virtual std::string GetPropertyString(const NFGUID& self, const std::string& propertyName) = 0;
	virtual NFGUID GetPropertyObject(const NFGUID& self, const std::string& propertyName) = 0;
	virtual NFVector2 GetPropertyVector2(const NFGUID& self, const std::string& propertyName) = 0;
	virtual NFVector3 GetPropertyVector3(const NFGUID& self, const std::string& propertyName) = 0;
};

#endif