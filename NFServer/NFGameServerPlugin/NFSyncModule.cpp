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


#include "NFSyncModule.h"
#include "NFComm/NFPluginModule/NFINetModule.h"
#include "NFComm/NFMessageDefine/NFMsgShare.pb.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"

bool NFSyncModule::Init()
{
	m_pScheduleModule = pPluginManager->FindModule<NFIScheduleModule>();
	m_pNetModule = pPluginManager->FindModule<NFINetModule>();
	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pGameServerNet_ServerModule = pPluginManager->FindModule<NFIGameServerNet_ServerModule>();
	m_pSceneModule = pPluginManager->FindModule<NFISceneModule>();
	m_pClassModule = pPluginManager->FindModule<NFIClassModule>();
	m_pLogModule = pPluginManager->FindModule<NFILogModule>();
	
    return true;
}

bool NFSyncModule::Shut()
{
    return true;
}

bool NFSyncModule::Execute()
{


    return true;
}

bool NFSyncModule::AfterInit()
{

	m_pKernelModule->AddClassCallBack(NFrame::NPC::ThisName(), this, &NFSyncModule::OnNPCClassEvent);
	m_pKernelModule->AddClassCallBack(NFrame::Player::ThisName(), this, &NFSyncModule::OnPlayerClassEvent);


    return true;
}

bool NFSyncModule::RequireMove(const NFGUID self, const NFVector3& pos, const int type)
{
	RequireStop(self);
	auto it = mPlayerPosition.find(self);
	if (it == mPlayerPosition.end())
	{
		mPlayerPosition.insert(std::map<NFGUID, NFVector3>::value_type(self, pos));
	}

	return true;
}

bool NFSyncModule::RequireStop(const NFGUID self)
{
	auto it = mPlayerPosition.find(self);
	if (it != mPlayerPosition.end())
	{
		mPlayerPosition.erase(it);
	}

	return true;
}


int NFSyncModule::SyncHeart(const std::string & strHeartName, const float time, const int count)
{
	//0.1s


	return 0;
}

int NFSyncModule::OnNPCClassEvent(const NFGUID & self, const std::string & className, const CLASS_OBJECT_EVENT classEvent, const NFDataList & var)
{
	if (CLASS_OBJECT_EVENT::COE_CREATE_FINISH == classEvent)
	{
	}

	return 0;
}

int NFSyncModule::OnNPCGMPositionEvent(const NFGUID & self, const std::string & propertyName, const NFData & oldVar, const NFData & newVar)
{
	return 0;
}

int NFSyncModule::OnPlayerClassEvent(const NFGUID & self, const std::string & className, const CLASS_OBJECT_EVENT classEvent, const NFDataList & var)
{
	if (CLASS_OBJECT_EVENT::COE_CREATE_FINISH == classEvent)
	{
		m_pKernelModule->AddPropertyCallBack(self, NFrame::Player::GMMoveTo(), this, &NFSyncModule::OnPlayerGMPositionEvent);
	}

	return 0;
}

int NFSyncModule::OnPlayerGMPositionEvent(const NFGUID & self, const std::string & propertyName, const NFData & oldVar, const NFData & newVar)
{
	NFMsg::ReqAckPlayerPosSync xMsg;
	NFMsg::PosSyncUnit* syncUnit = xMsg.add_sync_unit();
	if (syncUnit)
	{
		NFVector3 v = newVar.GetVector3();
		*syncUnit->mutable_pos() = NFINetModule::NFToPB(v);
		*syncUnit->mutable_mover() = NFINetModule::NFToPB(self);
		syncUnit->set_move_type(NFMsg::PosSyncUnit_EMoveType::PosSyncUnit_EMoveType_EET_TELEPORT);

		m_pKernelModule->SetPropertyVector3(self, NFrame::IObject::Position(), v);

		const int sceneID = m_pKernelModule->GetPropertyInt32(self, NFrame::Player::SceneID());
		const int groupID = m_pKernelModule->GetPropertyInt32(self, NFrame::Player::GroupID());

		m_pGameServerNet_ServerModule->SendGroupMsgPBToGate(NFMsg::ACK_MOVE_IMMUNE, xMsg, sceneID, groupID);
	}

	return 0;
}
