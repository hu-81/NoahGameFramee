﻿// -------------------------------------------------------------------------
//    @FileName			:    NFCSceneAOIModule.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2016-12-05
//    @Module           :    NFCSceneAOIModule
//
// -------------------------------------------------------------------------

#include "NFCSceneAOIModule.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"

bool NFCSceneAOIModule::Init()
{
	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pClassModule = pPluginManager->FindModule<NFIClassModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pLogModule = pPluginManager->FindModule<NFILogModule>();
	m_pEventModule = pPluginManager->FindModule<NFIEventModule>();

	m_pKernelModule->RegisterCommonClassEvent(this, &NFCSceneAOIModule::OnClassCommonEvent);
	m_pKernelModule->RegisterCommonPropertyEvent(this, &NFCSceneAOIModule::OnPropertyCommonEvent);
	m_pKernelModule->RegisterCommonRecordEvent(this, &NFCSceneAOIModule::OnRecordCommonEvent);

	//init all scene
	NF_SHARE_PTR<NFIClass> pLogicClass = m_pClassModule->GetElement(NFrame::Scene::ThisName());
	if (pLogicClass)
	{
		NFList<std::string>& strIdList = pLogicClass->GetIdList();

		std::string strId;
		bool bRet = strIdList.First(strId);
		while (bRet)
		{
			int nSceneID = lexical_cast<int>(strId);
			m_pKernelModule->CreateScene(nSceneID);

			bRet = strIdList.Next(strId);
		}
	}

    return true;
}

bool NFCSceneAOIModule::AfterInit()
{
	
    return true;
}

bool NFCSceneAOIModule::BeforeShut()
{
	mtObjectEnterCallback.clear();
	mtObjectLeaveCallback.clear();
	mtPropertyEnterCallback.clear();
	mtRecordEnterCallback.clear();
	mtPropertySingleCallback.clear();
	mtRecordSingleCallback.clear();

	mtAfterEnterSceneCallback.clear();
	mtBeforeLeaveSceneCallback.clear();

    return true;
}

bool NFCSceneAOIModule::Shut()
{
    return true;
}

bool NFCSceneAOIModule::Execute()
{
    return true;
}

bool NFCSceneAOIModule::RequestEnterScene(const NFGUID & self, const int nSceneID, const int nType, const NFIDataList & argList)
{
	return RequestEnterScene(self, nSceneID, -1, nType, argList);
}

bool NFCSceneAOIModule::RequestEnterScene(const NFGUID & self, const int nSceneID, const int nGrupID, const int nType, const NFIDataList & argList)
{
	const int nNowSceneID = m_pKernelModule->GetPropertyInt(self, NFrame::Player::SceneID());
	const int nNowGroupID = m_pKernelModule->GetPropertyInt(self, NFrame::Player::GroupID());
	
	if (nNowSceneID == nSceneID
		&& nNowGroupID == nGrupID)
	{
		m_pLogModule->LogNormal(NFILogModule::NLL_INFO_NORMAL, self, "in same scene and group but it not a clone scene", nSceneID);

		return false;
	}

	NF_SHARE_PTR<NFCSceneInfo> pSceneInfo = GetElement(nSceneID);
	if (!pSceneInfo)
	{
		return false;
	}

	NFINT64 nNewGroupID = nGrupID;
	if (nGrupID < 0)
	{
		//call in inner environments
		nNewGroupID = m_pKernelModule->RequestGroupScene(nSceneID);
	}
	else
	{
		if (!pSceneInfo->ExistElement(nNewGroupID))
		{
			return false;
		}
	}
	
	int nEnterConditionCode = EnterSceneCondition(self, nSceneID, nNewGroupID, nType, argList);
	if (nEnterConditionCode != 0)
	{
		m_pLogModule->LogNormal(NFILogModule::NLL_INFO_NORMAL, self, "before enter condition code:", nEnterConditionCode);
		return false;
	}

	if (!SwitchScene(self, nSceneID, nNewGroupID, nType, 0.0f, 0.0f, 0.0f, 0.0f, argList))
	{
		m_pLogModule->LogNormal(NFILogModule::NLL_INFO_NORMAL, self, "SwitchScene failed", nSceneID);

		return false;
	}

	return true;
}

bool NFCSceneAOIModule::AddSeedData(const int nSceneID, const std::string & strSeedID, const std::string & strConfigID, const NFVector3 & vPos)
{
	NF_SHARE_PTR<NFCSceneInfo> pSceneInfo = GetElement(nSceneID);
	if (pSceneInfo)
	{
		return pSceneInfo->AddSeedObjectInfo(strSeedID, strConfigID, vPos);
	}

	return false;
}

bool NFCSceneAOIModule::AddObjectEnterCallBack(const OBJECT_ENTER_EVENT_FUNCTOR_PTR & cb)
{
	mtObjectEnterCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddObjectLeaveCallBack(const OBJECT_LEAVE_EVENT_FUNCTOR_PTR & cb)
{
	mtObjectLeaveCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddPropertyEnterCallBack(const PROPERTY_ENTER_EVENT_FUNCTOR_PTR & cb)
{
	mtPropertyEnterCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddRecordEnterCallBack(const RECORD_ENTER_EVENT_FUNCTOR_PTR & cb)
{
	mtRecordEnterCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddPropertyEventCallBack(const PROPERTY_SINGLE_EVENT_FUNCTOR_PTR & cb)
{
	mtPropertySingleCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddRecordEventCallBack(const RECORD_SINGLE_EVENT_FUNCTOR_PTR & cb)
{
	mtRecordSingleCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddEnterSceneConditionCallBack(const SCENE_EVENT_FUNCTOR_PTR & cb)
{
	mtEnterSceneConditionCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddBeforeEnterSceneGroupCallBack(const SCENE_EVENT_FUNCTOR_PTR & cb)
{
	mtBeforeEnterSceneCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddAfterEnterSceneGroupCallBack(const SCENE_EVENT_FUNCTOR_PTR & cb)
{
	mtAfterEnterSceneCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddBeforeLeaveSceneGroupCallBack(const SCENE_EVENT_FUNCTOR_PTR & cb)
{
	mtBeforeLeaveSceneCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::AddAfterLeaveSceneGroupCallBack(const SCENE_EVENT_FUNCTOR_PTR & cb)
{
	mtAfterLeaveSceneCallback.push_back(cb);
	return true;
}

bool NFCSceneAOIModule::CreateSceneObject(const int nSceneID, const int nGroupID)
{
	NF_SHARE_PTR<NFCSceneInfo> pSceneInfo = GetElement(nSceneID);
	if (!pSceneInfo)
	{
		return false;
	}

	//prepare monster for player
	//create monster before the player enter the scene, then we can send monster's data by one message pack
	//if you create monster after player enter scene, then send monster's data one by one
	NF_SHARE_PTR<SceneSeedResource> pResource = pSceneInfo->mtSceneResourceConfig.First();
	while (pResource)
	{
		const std::string& strClassName = m_pElementModule->GetPropertyString(pResource->strConfigID, NFrame::IObject::ClassName());

		NFCDataList arg;
		arg << NFrame::IObject::X() << pResource->vSeedPos.X();
		arg << NFrame::IObject::Y() << pResource->vSeedPos.Y();
		arg << NFrame::IObject::Z() << pResource->vSeedPos.Z();
		arg << NFrame::NPC::SeedID() << pResource->strSeedID;

		m_pKernelModule->CreateObject(NFGUID(), nSceneID, nGroupID, strClassName, pResource->strConfigID, arg);

		pResource = pSceneInfo->mtSceneResourceConfig.Next();
	}

	return false;
}

bool NFCSceneAOIModule::SwitchScene(const NFGUID& self, const int nTargetSceneID, const int nTargetGroupID, const int nType, const float fX, const float fY, const float fZ, const float fOrient, const NFIDataList& arg)
{
	NF_SHARE_PTR<NFIObject> pObject = m_pKernelModule->GetObject(self);
	if (pObject)
	{
		NFINT64 nOldSceneID = pObject->GetPropertyInt(NFrame::Scene::SceneID());
		NFINT64 nOldGroupID = pObject->GetPropertyInt(NFrame::Scene::GroupID());

		NF_SHARE_PTR<NFCSceneInfo> pOldSceneInfo = this->GetElement(nOldSceneID);
		NF_SHARE_PTR<NFCSceneInfo> pNewSceneInfo = this->GetElement(nTargetSceneID);
		if (!pOldSceneInfo)
		{
			m_pLogModule->LogNormal(NFILogModule::NLL_ERROR_NORMAL, self, "no this container", nOldSceneID);
			return false;
		}

		if (!pNewSceneInfo)
		{
			m_pLogModule->LogNormal(NFILogModule::NLL_ERROR_NORMAL, self, "no this container", nTargetSceneID);
			return false;
		}

		if (!pNewSceneInfo->GetElement(nTargetGroupID))
		{
			m_pLogModule->LogNormal(NFILogModule::NLL_ERROR_NORMAL, self, "no this group", nTargetGroupID);
			return false;
		}
		/////////
		BeforeLeaveSceneGroup(self, nOldSceneID, nOldGroupID, nType, arg);

		pOldSceneInfo->RemoveObjectFromGroup(nOldGroupID, self, true);

		if (nTargetSceneID != nOldSceneID)
		{
			pObject->SetPropertyInt(NFrame::Scene::GroupID(), 0);
			/////////
			AfterLeaveSceneGroup(self, nOldSceneID, nOldGroupID, nType, arg);

			pObject->SetPropertyInt(NFrame::Scene::SceneID(), nTargetSceneID);

		}

		pObject->SetPropertyFloat(NFrame::IObject::X(), fX);
		pObject->SetPropertyFloat(NFrame::IObject::Y(), fY);
		pObject->SetPropertyFloat(NFrame::IObject::Z(), fZ);

		////////
		BeforeEnterSceneGroup(self, nTargetSceneID, nTargetGroupID, nType, arg);

		pNewSceneInfo->AddObjectToGroup(nTargetGroupID, self, true);
		pObject->SetPropertyInt(NFrame::Scene::GroupID(), nTargetGroupID);

		/////////
		AfterEnterSceneGroup(self, nTargetSceneID, nTargetGroupID, nType, arg);

		return true;
	}

	m_pLogModule->LogObject(NFILogModule::NLL_ERROR_NORMAL, self, "There is no object", __FUNCTION__, __LINE__);

	return false;
}

int NFCSceneAOIModule::OnPropertyCommonEvent(const NFGUID & self, const std::string & strPropertyName, const NFIDataList::TData & oldVar, const NFIDataList::TData & newVar)
{
	const std::string& strClassName = m_pKernelModule->GetPropertyString(self, NFrame::IObject::ClassName());
	if (strClassName == NFrame::Player::ThisName())
	{
		//only player can change grupid and sceneid
		if (NFrame::Player::GroupID() == strPropertyName)
		{
			OnPlayerGroupEvent(self, strPropertyName, oldVar, newVar);
			return 0;
		}

		if (NFrame::Player::SceneID() == strPropertyName)
		{
			OnPlayerSceneEvent(self, strPropertyName, oldVar, newVar);
			return 0;
		}
	}

	NFCDataList valueBroadCaseList;
	if (GetBroadCastObject(self, strPropertyName, false, valueBroadCaseList) <= 0)
	{
		return 0;
	}

	OnPropertyEvent(self, strPropertyName, oldVar, newVar, valueBroadCaseList);

	return 0;
}

int NFCSceneAOIModule::OnRecordCommonEvent(const NFGUID & self, const RECORD_EVENT_DATA & xEventData, const NFIDataList::TData & oldVar, const NFIDataList::TData & newVar)
{
	const std::string& strRecordName = xEventData.strRecordName;
	const int nOpType = xEventData.nOpType;
	const int nRow = xEventData.nRow;
	const int nCol = xEventData.nCol;

	int nObjectContainerID = m_pKernelModule->GetPropertyInt(self, NFrame::Player::SceneID());
	int nObjectGroupID = m_pKernelModule->GetPropertyInt(self, NFrame::Player::GroupID());

	if (nObjectGroupID < 0)
	{
		return 0;
	}
	
	NFCDataList valueBroadCaseList;
	GetBroadCastObject(self, strRecordName, true, valueBroadCaseList);

	OnRecordEvent(self, strRecordName, xEventData, oldVar, newVar, valueBroadCaseList);

	return 0;
}

int NFCSceneAOIModule::OnClassCommonEvent(const NFGUID & self, const std::string & strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList & var)
{
	if (CLASS_OBJECT_EVENT::COE_DESTROY == eClassEvent)
	{
		const int nObjectSceneID = m_pKernelModule->GetPropertyInt(self, NFrame::IObject::SceneID());
		const int nObjectGroupID = m_pKernelModule->GetPropertyInt(self, NFrame::IObject::GroupID());

		if (nObjectGroupID < 0 || nObjectSceneID <= 0)
		{
			return 0;
		}

		NFCDataList valueAllPlayrNoSelfList;
		m_pKernelModule->GetGroupObjectList(nObjectSceneID, nObjectGroupID, valueAllPlayrNoSelfList, true, self);

		//tell other people that you want to leave from this scene or this group
		//every one want to know you want to leave notmater you are a monster maybe you are a player
		OnObjectListLeave(valueAllPlayrNoSelfList, NFCDataList() << self);
	}

	else if (CLASS_OBJECT_EVENT::COE_CREATE_NODATA == eClassEvent)
	{

	}
	else if (CLASS_OBJECT_EVENT::COE_CREATE_LOADDATA == eClassEvent)
	{
	}
	else if (CLASS_OBJECT_EVENT::COE_CREATE_HASDATA == eClassEvent)
	{
		if (strClassName == NFrame::Player::ThisName())
		{
			//tell youself<client>, u want to enter this scene or this group
			OnObjectListEnter(NFCDataList() << self, NFCDataList() << self);

			//tell youself<client>, u want to broad your properties and records to youself
			OnPropertyEnter(NFCDataList() << self, self);
			OnRecordEnter(NFCDataList() << self, self);
		}
		else
		{
			const int nObjectSceneID = m_pKernelModule->GetPropertyInt(self, NFrame::IObject::SceneID());
			const int nObjectGroupID = m_pKernelModule->GetPropertyInt(self, NFrame::IObject::GroupID());

			if (nObjectGroupID < 0 || nObjectSceneID <= 0)
			{
				return 0;
			}

			NFCDataList valueAllPlayrObjectList;
			m_pKernelModule->GetGroupObjectList(nObjectSceneID, nObjectGroupID, valueAllPlayrObjectList, true);

			//monster or others need to tell all player
			OnObjectListEnter(valueAllPlayrObjectList, NFCDataList() << self);
			OnPropertyEnter(valueAllPlayrObjectList, self);
		}
	}
	else if (CLASS_OBJECT_EVENT::COE_CREATE_FINISH == eClassEvent)
	{

	}

	return 0;
}

int NFCSceneAOIModule::OnPlayerGroupEvent(const NFGUID & self, const std::string & strPropertyName, const NFIDataList::TData & oldVar, const NFIDataList::TData & newVar)
{
	//this event only happened in the same scene
	int nSceneID = m_pKernelModule->GetPropertyInt(self, NFrame::IObject::SceneID());
	int nOldGroupID = oldVar.GetInt();
	int nNewGroupID = newVar.GetInt();

	//maybe form 0, maybe not, only three stuation
	//example1: 0 -> 1 ==> new_group > 0 && old_group <= 0
	//example2: 1 -> 2 ==> new_group > 0 && old_group > 0
	//example3: 5 -> 0 ==> new_group <= 0 && old_group > 0
	if (nNewGroupID > 0)
	{
		if (nOldGroupID > 0)
		{
			//example2: 1 -> 2 ==> new_group > 0 && old_group > 0
			//step1: leave
			NFCDataList valueAllOldNPCListNoSelf;
			NFCDataList valueAllOldPlayerListNoSelf;
			m_pKernelModule->GetGroupObjectList(nSceneID, nOldGroupID, valueAllOldNPCListNoSelf, false, self);
			m_pKernelModule->GetGroupObjectList(nSceneID, nOldGroupID, valueAllOldPlayerListNoSelf, true, self);

			OnObjectListLeave(valueAllOldPlayerListNoSelf, NFCDataList() << self);
			OnObjectListLeave(NFCDataList() << self, valueAllOldPlayerListNoSelf);
			OnObjectListLeave(NFCDataList() << self, valueAllOldNPCListNoSelf);
		}
		else
		{
			//example1: 0 -> 1 == > new_group > 0 && old_group <= 0
			//only use step2 that enough
		}

		//step2: enter
		NFCDataList valueAllNewNPCListNoSelf;
		NFCDataList valueAllNewPlayerListNoSelf;

		m_pKernelModule->GetGroupObjectList(nSceneID, nNewGroupID, valueAllNewNPCListNoSelf, false, self);
		m_pKernelModule->GetGroupObjectList(nSceneID, nNewGroupID, valueAllNewPlayerListNoSelf, true, self);

		OnObjectListEnter(valueAllNewPlayerListNoSelf, NFCDataList() << self);
		OnObjectListEnter(NFCDataList() << self, valueAllNewPlayerListNoSelf);
		OnObjectListEnter(NFCDataList() << self, valueAllNewNPCListNoSelf);

		//bc others data to u
		for (int i = 0; i < valueAllNewNPCListNoSelf.GetCount(); i++)
		{
			NFGUID identOld = valueAllNewNPCListNoSelf.Object(i);

			OnPropertyEnter(NFCDataList() << self, identOld);
			OnRecordEnter(NFCDataList() << self, identOld);
		}

		//bc others data to u
		for (int i = 0; i < valueAllNewPlayerListNoSelf.GetCount(); i++)
		{
			NFGUID identOld = valueAllNewPlayerListNoSelf.Object(i);

			OnPropertyEnter(NFCDataList() << self, identOld);
			OnRecordEnter(NFCDataList() << self, identOld);
		}

		//bc u data to others
		OnPropertyEnter(valueAllNewPlayerListNoSelf, self);
		OnRecordEnter(valueAllNewPlayerListNoSelf, self);
	}
	else
	{
		if (nOldGroupID > 0)
		{
			//example3: 5 -> 0 ==> new_group <= 0 && old_group > 0
			//step1: leave
			NFCDataList valueAllOldNPCListNoSelf;
			NFCDataList valueAllOldPlayerListNoSelf;
			m_pKernelModule->GetGroupObjectList(nSceneID, nOldGroupID, valueAllOldNPCListNoSelf, false, self);
			m_pKernelModule->GetGroupObjectList(nSceneID, nOldGroupID, valueAllOldPlayerListNoSelf, true, self);

			OnObjectListLeave(valueAllOldPlayerListNoSelf, NFCDataList() << self);
			OnObjectListLeave(NFCDataList() << self, valueAllOldPlayerListNoSelf);
			OnObjectListLeave(NFCDataList() << self, valueAllOldNPCListNoSelf);
		}
	}

	return 0;
}

int NFCSceneAOIModule::OnPlayerSceneEvent(const NFGUID & self, const std::string & strPropertyName, const NFIDataList::TData & oldVar, const NFIDataList::TData & newVar)
{
	//no more player in this group of this scene at the same time
	//so now only one player(that you) in this group of this scene
	//BTW, most of time, we dont create monsters in the group 0
	//so no one at this group but u

	return 0;
}

int NFCSceneAOIModule::GetBroadCastObject(const NFGUID & self, const std::string & strPropertyName, const bool bTable, NFIDataList & valueObject)
{
	int nObjectContainerID = m_pKernelModule->GetPropertyInt(self, NFrame::IObject::SceneID());
	int nObjectGroupID = m_pKernelModule->GetPropertyInt(self, NFrame::IObject::GroupID());

	const std::string& strClassName = m_pKernelModule->GetPropertyString(self, NFrame::IObject::ClassName());
	NF_SHARE_PTR<NFIRecordManager> pClassRecordManager = m_pClassModule->GetClassRecordManager(strClassName);
	NF_SHARE_PTR<NFIPropertyManager> pClassPropertyManager = m_pClassModule->GetClassPropertyManager(strClassName);

	NF_SHARE_PTR<NFIRecord> pRecord(NULL);
	NF_SHARE_PTR<NFIProperty> pProperty(NULL);
	if (bTable)
	{
		if (NULL == pClassRecordManager)
		{
			return -1;
		}

		pRecord = pClassRecordManager->GetElement(strPropertyName);
		if (NULL == pRecord)
		{
			return -1;
		}
	}
	else
	{
		if (NULL == pClassPropertyManager)
		{
			return -1;
		}
		pProperty = pClassPropertyManager->GetElement(strPropertyName);
		if (NULL == pProperty)
		{
			return -1;
		}
	}

	if (bTable)
	{
		if (pRecord->GetPublic())
		{
			m_pKernelModule->GetGroupObjectList(nObjectContainerID, nObjectGroupID, valueObject, true, self);
		}
		else if (pRecord->GetPrivate() && !pRecord->GetUpload())
		{//upload property can not board to itself
			valueObject.Add(self);
		}
	}
	else
	{
		if (pProperty->GetPublic())
		{
			m_pKernelModule->GetGroupObjectList(nObjectContainerID, nObjectGroupID, valueObject, true, self);
		}
		else if (pProperty->GetPrivate() && !pProperty->GetUpload())
		{
			//upload property can not board to itself
			valueObject.Add(self);
		}
	}

	return valueObject.GetCount();
}

int NFCSceneAOIModule::EnterSceneCondition(const NFGUID & self, const int nSceneID, const int nGroupID, const int nType, const NFIDataList & argList)
{
	std::vector<SCENE_EVENT_FUNCTOR_PTR>::iterator it = mtEnterSceneConditionCallback.begin();
	for (; it != mtEnterSceneConditionCallback.end(); it++)
	{
		SCENE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		SCENE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		const int nReason = pFunc->operator()(self, nSceneID, nGroupID, nType, argList);
		if (nReason != 0)
		{
			return nReason;
		}
	}
	return 0;
}

int NFCSceneAOIModule::AfterEnterSceneGroup(const NFGUID & self, const int nSceneID, const int nGroupID, const int nType, const NFIDataList & argList)
{
	std::vector<SCENE_EVENT_FUNCTOR_PTR>::iterator it = mtAfterEnterSceneCallback.begin();
	for (; it != mtAfterEnterSceneCallback.end(); it++)
	{
		SCENE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		SCENE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(self, nSceneID, nGroupID, nType, argList);
	}

	return 0;
}

int NFCSceneAOIModule::BeforeLeaveSceneGroup(const NFGUID & self, const int nSceneID, const int nGroupID, const int nType, const NFIDataList & argList)
{
	std::vector<SCENE_EVENT_FUNCTOR_PTR>::iterator it = mtBeforeLeaveSceneCallback.begin();
	for (; it != mtBeforeLeaveSceneCallback.end(); it++)
	{
		SCENE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		SCENE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(self, nSceneID, nGroupID, nType, argList);
	}

	return 0;
}

int NFCSceneAOIModule::AfterLeaveSceneGroup(const NFGUID & self, const int nSceneID, const int nGroupID, const int nType, const NFIDataList & argList)
{
	std::vector<SCENE_EVENT_FUNCTOR_PTR>::iterator it = mtAfterLeaveSceneCallback.begin();
	for (; it != mtAfterLeaveSceneCallback.end(); it++)
	{
		SCENE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		SCENE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(self, nSceneID, nGroupID, nType, argList);
	}

	return 0;
}

int NFCSceneAOIModule::BeforeEnterSceneGroup(const NFGUID & self, const int nSceneID, const int nGroupID, const int nType, const NFIDataList & argList)
{
	std::vector<SCENE_EVENT_FUNCTOR_PTR>::iterator it = mtBeforeEnterSceneCallback.begin();
	for (; it != mtBeforeEnterSceneCallback.end(); it++)
	{
		SCENE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		SCENE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(self, nSceneID, nGroupID, nType, argList);
	}
	return 0;
}

int NFCSceneAOIModule::OnObjectListEnter(const NFIDataList & self, const NFIDataList & argVar)
{
	std::vector<OBJECT_ENTER_EVENT_FUNCTOR_PTR>::iterator it = mtObjectEnterCallback.begin();
	for (; it != mtObjectEnterCallback.end(); it++)
	{
		OBJECT_ENTER_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		OBJECT_ENTER_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(self, argVar);
	}

	return 0;
}

int NFCSceneAOIModule::OnObjectListLeave(const NFIDataList & self, const NFIDataList & argVar)
{
	std::vector<OBJECT_LEAVE_EVENT_FUNCTOR_PTR>::iterator it = mtObjectLeaveCallback.begin();
	for (; it != mtObjectLeaveCallback.end(); it++)
	{
		OBJECT_LEAVE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		OBJECT_LEAVE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(self, argVar);
	}

	return 0;
}

int NFCSceneAOIModule::OnPropertyEnter(const NFIDataList & argVar, const NFGUID & self)
{
	std::vector<PROPERTY_ENTER_EVENT_FUNCTOR_PTR>::iterator it = mtPropertyEnterCallback.begin();
	for (; it != mtPropertyEnterCallback.end(); it++)
	{
		PROPERTY_ENTER_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		PROPERTY_ENTER_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(argVar, self);
	}

	return 0;
}

int NFCSceneAOIModule::OnRecordEnter(const NFIDataList & argVar, const NFGUID & self)
{
	std::vector<RECORD_ENTER_EVENT_FUNCTOR_PTR>::iterator it = mtRecordEnterCallback.begin();
	for (; it != mtRecordEnterCallback.end(); it++)
	{
		RECORD_ENTER_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		RECORD_ENTER_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(argVar, self);
	}

	return 0;
}

int NFCSceneAOIModule::OnPropertyEvent(const NFGUID & self, const std::string & strProperty, const NFIDataList::TData & oldVar, const NFIDataList::TData & newVar, const NFIDataList& argVar)
{
	std::vector<PROPERTY_SINGLE_EVENT_FUNCTOR_PTR>::iterator it = mtPropertySingleCallback.begin();
	for (; it != mtPropertySingleCallback.end(); it++)
	{
		PROPERTY_SINGLE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		PROPERTY_SINGLE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(self, strProperty, oldVar, newVar, argVar);
	}

	return 0;
}

int NFCSceneAOIModule::OnRecordEvent(const NFGUID & self, const std::string& strProperty, const RECORD_EVENT_DATA & xEventData, const NFIDataList::TData & oldVar, const NFIDataList::TData & newVar, const NFIDataList& argVar)
{
	std::vector<RECORD_SINGLE_EVENT_FUNCTOR_PTR>::iterator it = mtRecordSingleCallback.begin();
	for (; it != mtRecordSingleCallback.end(); it++)
	{
		RECORD_SINGLE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		RECORD_SINGLE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		pFunc->operator()(self, strProperty, xEventData, oldVar, newVar, argVar);
	}

	return 0;
}
