// -------------------------------------------------------------------------
//    @FileName			:    NFCPlayerRedisModule.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2013-10-03
//    @Module           :    NFCPlayerRedisModule
//    @Desc             :
// -------------------------------------------------------------------------
#include "NFCPlayerRedisModule.h"

NFCPlayerRedisModule::NFCPlayerRedisModule(NFIPluginManager * p)
{
	pPluginManager = p;
}

bool NFCPlayerRedisModule::Init()
{
	return true;
}

bool NFCPlayerRedisModule::Shut()
{
	return true;
}

bool NFCPlayerRedisModule::Execute()
{
	return true;
}

bool NFCPlayerRedisModule::AfterInit()
{
	m_pLogicClassModule = pPluginManager->FindModule<NFIClassModule>();
	m_pNoSqlModule = pPluginManager->FindModule<NFINoSqlModule>();
	m_pCommonRedisModule = pPluginManager->FindModule<NFICommonRedisModule>();
	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();

	m_pKernelModule->AddClassCallBack(NFrame::Player::ThisName(), this, &NFCPlayerRedisModule::OnObjectClassEvent);

	return true;
}

int64_t NFCPlayerRedisModule::GetPlayerCacheGameID(const NFGUID & self)
{
	NF_SHARE_PTR<NFINoSqlDriver> pNoSqlDriver = m_pNoSqlModule->GetDriverBySuitConsistent();
	if (!pNoSqlDriver)
	{
		return 0;
	}

	std::string strValue;
	int64_t nGameID = 0;
	std::string strKey = GetOnlineGameServerKey();

	if (pNoSqlDriver->HGet(strKey, self.ToString(), strValue))
	{
		try
		{
			nGameID = lexical_cast<int64_t>(strValue);
		}
		catch (...)
		{
		}
	}

	return nGameID;
}

int64_t NFCPlayerRedisModule::GetPlayerCacheProxyID(const NFGUID & self)
{
	NF_SHARE_PTR<NFINoSqlDriver> pNoSqlDriver = m_pNoSqlModule->GetDriverBySuitConsistent();
	if (!pNoSqlDriver)
	{
		return 0;
	}

	std::string strValue;
	int64_t nProxyID = 0;
	std::string strKey = GetOnlineProxyServerKey();

	if (pNoSqlDriver->HGet(strKey, self.ToString(), strValue))
	{
		try
		{
			nProxyID = lexical_cast<int64_t>(strValue);
		}
		catch (...)
		{
		}
	}

	return nProxyID;
}

bool NFCPlayerRedisModule::GetPlayerCacheGameID(const std::vector<std::string>& xList, std::vector<int64_t>& xResultList)
{
	NF_SHARE_PTR<NFINoSqlDriver> pNoSqlDriver = m_pNoSqlModule->GetDriverBySuitConsistent();
	if (!pNoSqlDriver)
	{
		return 0;
	}

	std::string strKey = GetOnlineGameServerKey();
	std::vector<std::string> strValueList;

	if (pNoSqlDriver->HMGet(strKey, xList, strValueList))
	{
		for (int i = 0; i < strValueList.size(); ++i)
		{
			int64_t nGameID = 0;

			try
			{
				nGameID = lexical_cast<int64_t>(strValueList[i]);
			}
			catch (...)
			{
			}

			xResultList.push_back(nGameID);
		}

		return true;
	}

	return false;
}

bool NFCPlayerRedisModule::GetPlayerCacheProxyID(const std::vector<std::string>& xList, std::vector<int64_t>& xResultList)
{
	NF_SHARE_PTR<NFINoSqlDriver> pNoSqlDriver = m_pNoSqlModule->GetDriverBySuitConsistent();
	if (!pNoSqlDriver)
	{
		return 0;
	}

	std::string strKey = GetOnlineProxyServerKey();
	std::vector<std::string> strValueList;

	if (pNoSqlDriver->HMGet(strKey, xList, strValueList))
	{
		for (int i = 0; i < strValueList.size(); ++i)
		{
			int64_t nProxyID = 0;

			try
			{
				nProxyID = lexical_cast<int64_t>(strValueList[i]);
			}
			catch (...)
			{
			}

			xResultList.push_back(nProxyID);
		}

		return true;
	}

	return false;
}

NF_SHARE_PTR<NFIPropertyManager> NFCPlayerRedisModule::GetPlayerCacheProperty(const NFGUID& self)
{
	return m_pCommonRedisModule->GetCachePropertyInfo(self, NFrame::Player::ThisName());
}

NF_SHARE_PTR<NFIRecordManager> NFCPlayerRedisModule::GetPlayerCacheRecord(const NFGUID& self)
{
	return m_pCommonRedisModule->GetCacheRecordInfo(self, NFrame::Player::ThisName());
}

bool NFCPlayerRedisModule::SetPlayerCacheProperty(const NFGUID& self, NF_SHARE_PTR<NFIPropertyManager> pPropertyManager)
{
	if (pPropertyManager == nullptr)
	{
		return false;
	}

	if (!m_pCommonRedisModule->SetCachePropertyInfo(self, pPropertyManager))
	{
		return false;
	}

	return true;
}

bool NFCPlayerRedisModule::SetPlayerCacheRecord(const NFGUID& self, NF_SHARE_PTR<NFIRecordManager> pRecordManager)
{
	if (pRecordManager == nullptr)
	{
		return false;
	}

	if (!m_pCommonRedisModule->SetCacheRecordInfo(self, pRecordManager))
	{
		return false;
	}

	return true;
}

bool NFCPlayerRedisModule::SavePlayerTileToCache(const int nSceneID, const NFGUID & self, const std::string & strTileData)
{
	std::string strTileKey = m_pCommonRedisModule->GetTileCacheKey(nSceneID);
	NF_SHARE_PTR<NFINoSqlDriver> xNoSqlDriver = m_pNoSqlModule->GetDriverBySuitRandom();
	if (xNoSqlDriver)
	{
		return xNoSqlDriver->HSet(strTileKey, self.ToString(), strTileData);
	}

	return false;
}

bool NFCPlayerRedisModule::GetPlayerTileFromCache(const int nSceneID, const NFGUID & self, std::string & strTileData)
{
	std::string strTileKey = m_pCommonRedisModule->GetTileCacheKey(nSceneID);
	NF_SHARE_PTR<NFINoSqlDriver> xNoSqlDriver = m_pNoSqlModule->GetDriverBySuitRandom();
	if (xNoSqlDriver && xNoSqlDriver->Exists(strTileKey))
	{
		return xNoSqlDriver->HGet(strTileKey, self.ToString(), strTileData);
	}

	return false;
}

bool NFCPlayerRedisModule::GetPlayerTileRandomFromCache(const int nSceneID, std::string & strTileData)
{
	std::string strTileKey = m_pCommonRedisModule->GetTileCacheKey(nSceneID);
	NF_SHARE_PTR<NFINoSqlDriver> xNoSqlDriver = m_pNoSqlModule->GetDriverBySuitRandom();
	if (xNoSqlDriver && xNoSqlDriver->Exists(strTileKey))
	{
		//need t cache this keys
		std::vector<std::string> vKeys;
		if (xNoSqlDriver->HKeys(strTileKey, vKeys))
		{
			int nKeyIndex = m_pKernelModule->Random(0, vKeys.size());
			std::string strKey = vKeys[nKeyIndex];
			if (xNoSqlDriver->HGet(strTileKey, strKey, strTileData))
			{
				return true;
			}
		}
	}

	return false;
}

bool NFCPlayerRedisModule::SavePlayerDataToCache(const NFGUID & self)
{
	bool isProperty = SetPlayerCacheProperty(self, m_pKernelModule->GetObject(self)->GetPropertyManager());
	bool isRecord = SetPlayerCacheRecord(self, m_pKernelModule->GetObject(self)->GetRecordManager());

	return isProperty && isRecord;
}

std::string NFCPlayerRedisModule::GetOnlineGameServerKey()
{
	//if (strValue == "**nonexistent-key**")
	return "OnlineGameKey";
}

std::string NFCPlayerRedisModule::GetOnlineProxyServerKey()
{
	return "OnlineProxyKey";
}

const bool NFCPlayerRedisModule::AttachData(const NFGUID & self)
{
	if (mxObjectDataCache.ExistElement(self))
	{
		//way 1:load first then create object, especially we have loaded nosql plugin
	}
	else
	{
		//way 2:load data when creating a object, especially we donot loaded any sql or nosql plugin
	}

	NF_SHARE_PTR<NFIObject> pObject = m_pKernelModule->GetObject(self);
	if (!pObject)
	{
		return false;
	}
	NF_SHARE_PTR<NFIPropertyManager> pPropertyManager = pObject->GetPropertyManager();
	NF_SHARE_PTR<NFIRecordManager> pRecordManager = pObject->GetRecordManager();

	NFMsg::ObjectPropertyList xPbPropertyList;
	if (m_pCommonRedisModule->GetCachePropertyListPB(self, xPbPropertyList))
	{
		m_pCommonRedisModule->ConvertPBToPropertyManager(xPbPropertyList, pPropertyManager, true);
	}
	if (m_pCommonRedisModule->GetStoragePropertyListPB(self, xPbPropertyList))
	{
		m_pCommonRedisModule->ConvertPBToPropertyManager(xPbPropertyList, pPropertyManager, false);
	}
	NFMsg::ObjectRecordList xPbRecordList;
	if (m_pCommonRedisModule->GetCacheRecordListPB(self, xPbRecordList))
	{
		m_pCommonRedisModule->ConvertPBToRecordManager(xPbRecordList, pRecordManager, true);
	}
	if (m_pCommonRedisModule->GetStorageRecordListPB(self, xPbRecordList))
	{
		m_pCommonRedisModule->ConvertPBToRecordManager(xPbRecordList, pRecordManager, false);
	}

	return true;
}

int NFCPlayerRedisModule::OnObjectClassEvent(const NFGUID & self, const std::string & strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFDataList & var)
{
	if (CLASS_OBJECT_EVENT::COE_DESTROY == eClassEvent)
	{
		OnOffline(self);
		//NFINT64 xT1 = NFGetTime();
		//m_pKernelModule->SetPropertyInt(self, NFrame::Player::LastOfflineTime(), xT1);

		//const NFINT64& xT2 = m_pKernelModule->GetPropertyInt(self, NFrame::Player::OnlineTime());

		//NFINT64 totalTime = m_pKernelModule->GetPropertyInt(self, NFrame::Player::TotalTime());
		//m_pKernelModule->SetPropertyInt(self, NFrame::Player::TotalTime(), totalTime + xT1 - xT2);

		SavePlayerDataToCache(self);
	}
	else if (CLASS_OBJECT_EVENT::COE_CREATE_LOADDATA == eClassEvent)
	{
		OnOnline(self);
		AttachData(self);

		//m_pKernelModule->SetPropertyInt(self, NFrame::Player::OnlineTime(), NFGetTime());
		//int nOnlineCount = m_pKernelModule->GetPropertyInt(self, NFrame::Player::OnlineCount());
		//m_pKernelModule->SetPropertyInt(self, NFrame::Player::OnlineCount(), (nOnlineCount + 1));
	}

	return 0;
}

void NFCPlayerRedisModule::OnOnline(const NFGUID & self)
{
	const int nGateID = m_pKernelModule->GetPropertyInt(self, NFrame::Player::GateID());
	const int nServerID = m_pKernelModule->GetPropertyInt(self, NFrame::Player::GameID());
}

void NFCPlayerRedisModule::OnOffline(const NFGUID & self)
{
	const int nGateID = 0;
	const int nServerID = 0;
}
