
// -------------------------------------------------------------------------
//    @FileName         :    NFCNetClientModule.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2017-02-15
//    @Module           :    NFCNetClientModule
//
// -------------------------------------------------------------------------

#include "NFCNetModule.h"
#include "NFCNetClientModule.h"

NFCNetClientModule::NFCNetClientModule(NFIPluginManager * p)
{
	pPluginManager = p;
}

bool NFCNetClientModule::Init()
{
	for (int i = 0; i < NF_SERVER_TYPES::NF_ST_MAX; ++i)
	{
		NFINetClientModule::AddEventCallBack((NF_SERVER_TYPES)i, this, &NFCNetClientModule::OnSocketEvent);
	}

	return true;
}

bool NFCNetClientModule::AfterInit()
{
	return true;
}

bool NFCNetClientModule::BeforeShut()
{
	return true;
}

bool NFCNetClientModule::Shut()
{
	return true;
}

bool NFCNetClientModule::Execute()
{
	ProcessExecute();
	ProcessAddNetConnect();

	return true;
}

void NFCNetClientModule::RemoveReceiveCallBack(NF_SERVER_TYPES eType, const int nMsgID)
{
	NF_SHARE_PTR<CallBack> xCallBack = mxCallBack.GetElement(eType);
	if (xCallBack)
	{
		std::map<int, NET_RECEIVE_FUNCTOR_PTR>::iterator it = xCallBack->mxReceiveCallBack.find(nMsgID);
		if (xCallBack->mxReceiveCallBack.end() == it)
		{
			xCallBack->mxReceiveCallBack.erase(it);
		}
	}
}

void NFCNetClientModule::AddServer(const ConnectData & xInfo)
{
	mxTempNetList.push_back(xInfo);
}

int NFCNetClientModule::AddReceiveCallBack(NF_SERVER_TYPES eType, const int nMsgID, NET_RECEIVE_FUNCTOR_PTR functorPtr)
{
	NF_SHARE_PTR<CallBack> xCallBack = mxCallBack.GetElement(eType);
	if (!xCallBack)
	{
		xCallBack = NF_SHARE_PTR<CallBack>(NF_NEW CallBack);
		mxCallBack.AddElement(eType, xCallBack);
	}

	xCallBack->mxReceiveCallBack.insert(std::map<int, NET_RECEIVE_FUNCTOR_PTR>::value_type(nMsgID, functorPtr));

	return 0;
}

int NFCNetClientModule::AddReceiveCallBack(NF_SERVER_TYPES eType, NET_RECEIVE_FUNCTOR_PTR functorPtr)
{
	NF_SHARE_PTR<CallBack> xCallBack = mxCallBack.GetElement(eType);
	if (!xCallBack)
	{
		xCallBack = NF_SHARE_PTR<CallBack>(NF_NEW CallBack);
		mxCallBack.AddElement(eType, xCallBack);
	}

	xCallBack->mxCallBackList.push_back(functorPtr);

	return 0;
}


int NFCNetClientModule::AddEventCallBack(NF_SERVER_TYPES eType, NET_EVENT_FUNCTOR_PTR functorPtr)
{
	NF_SHARE_PTR<CallBack> xCallBack = mxCallBack.GetElement(eType);
	if (!xCallBack)
	{
		xCallBack = NF_SHARE_PTR<CallBack>(NF_NEW CallBack);
		mxCallBack.AddElement(eType, xCallBack);
	}

	xCallBack->mxEventCallBack.push_back(functorPtr);
	return 0;
}

void NFCNetClientModule::SendByServerID(const int nServerID, const int nMsgID, const std::string & strData)
{
	SendByServerID(nServerID, nMsgID, strData.c_str(), strData.length());
}

void NFCNetClientModule::SendByServerID(const int nServerID, const int nMsgID, const char * msg, const uint32_t nLen)
{
	NF_SHARE_PTR<ConnectData> pServer = mxServerMap.GetElement(nServerID);
	if (pServer)
	{
		NF_SHARE_PTR<NFINetModule> pNetModule = pServer->mxNetModule;
		if (pNetModule.get())
		{
			pNetModule->GetNet()->SendMsgWithOutHead(nMsgID, msg, nLen, 0);
		}
	}
}

void NFCNetClientModule::SendToAllServer(const int nMsgID, const std::string & strData)
{
	NF_SHARE_PTR<ConnectData> pServer = mxServerMap.First();
	while (pServer)
	{
		NF_SHARE_PTR<NFINetModule> pNetModule = pServer->mxNetModule;
		if (pNetModule.get())
		{
			pNetModule->SendMsgWithOutHead(nMsgID, strData, 0);
		}

		pServer = mxServerMap.Next();
	}
}

void NFCNetClientModule::SendToAllServer(NF_SERVER_TYPES eType, const int nMsgID, const std::string & strData)
{
}

void NFCNetClientModule::SendToServerByPB(const int nServerID, const uint16_t nMsgID, google::protobuf::Message & xData)
{
	NF_SHARE_PTR<ConnectData> pServer = mxServerMap.GetElement(nServerID);
	if (pServer)
	{
		NF_SHARE_PTR<NFINetModule> pNetModule = pServer->mxNetModule;
		if (pNetModule.get())
		{
			pNetModule->SendMsgPB(nMsgID, xData, 0, NFGUID(), NULL);
		}
	}
}

void NFCNetClientModule::SendToAllServerByPB(const uint16_t nMsgID, google::protobuf::Message & xData)
{
	NF_SHARE_PTR<ConnectData> pServer = mxServerMap.First();
	while (pServer)
	{
		NF_SHARE_PTR<NFINetModule> pNetModule = pServer->mxNetModule;
		if (pNetModule.get())
		{
			pNetModule->SendMsgPB(nMsgID, xData, 0);
		}

		pServer = mxServerMap.Next();
	}
}

void NFCNetClientModule::SendToAllServerByPB(NF_SERVER_TYPES eType, const uint16_t nMsgID, google::protobuf::Message & xData)
{
}

void NFCNetClientModule::SendBySuit(const std::string & strHashKey, const int nMsgID, const std::string & strData)
{
	uint32_t nCRC32 = NFrame::CRC32(strHashKey);
	SendBySuit(nCRC32, nMsgID, strData);
}

void NFCNetClientModule::SendBySuit(NF_SERVER_TYPES eType, const std::string & strHashKey, const int nMsgID, const std::string & strData)
{
}

void NFCNetClientModule::SendBySuit(const std::string & strHashKey, const int nMsgID, const char * msg, const uint32_t nLen)
{
	uint32_t nCRC32 = NFrame::CRC32(strHashKey);
	SendBySuit(nCRC32, nMsgID, msg, nLen);
}

void NFCNetClientModule::SendBySuit(NF_SERVER_TYPES eType, const std::string & strHashKey, const int nMsgID, const char * msg, const uint32_t nLen)
{
}

void NFCNetClientModule::SendBySuit(const int & nHashKey, const int nMsgID, const std::string & strData)
{
	SendBySuit(nHashKey, nMsgID, strData.c_str(), strData.length());
}

void NFCNetClientModule::SendBySuit(NF_SERVER_TYPES eType, const int & nHashKey, const int nMsgID, const std::string & strData)
{
}

void NFCNetClientModule::SendBySuit(const int & nHashKey, const int nMsgID, const char * msg, const uint32_t nLen)
{
	NF_SHARE_PTR<ConnectData> pConnectData = mxServerMap.GetElementBySuit(nHashKey);
	if (pConnectData)
	{

	}

	SendByServerID(pConnectData->nGameID, nMsgID, msg, nLen);
}

void NFCNetClientModule::SendBySuit(NF_SERVER_TYPES eType, const int & nHashKey, const int nMsgID, const char * msg, const uint32_t nLen)
{
}

void NFCNetClientModule::SendSuitByPB(const std::string & strHashKey, const uint16_t nMsgID, google::protobuf::Message & xData)
{
	uint32_t nCRC32 = NFrame::CRC32(strHashKey);
	SendSuitByPB(nCRC32, nMsgID, xData);
}

void NFCNetClientModule::SendSuitByPB(NF_SERVER_TYPES eType, const std::string & strHashKey, const uint16_t nMsgID, google::protobuf::Message & xData)
{
}

void NFCNetClientModule::SendSuitByPB(const int & nHashKey, const uint16_t nMsgID, google::protobuf::Message & xData)
{
	NF_SHARE_PTR<ConnectData> pConnectData = mxServerMap.GetElementBySuit(nHashKey);
	if (pConnectData)
	{

	}
	SendToServerByPB(pConnectData->nGameID, nMsgID, xData);
}

void NFCNetClientModule::SendSuitByPB(NF_SERVER_TYPES eType, const int & nHashKey, const uint16_t nMsgID, google::protobuf::Message & xData)
{
}

NF_SHARE_PTR<ConnectData> NFCNetClientModule::GetServerNetInfo(const int nServerID)
{
	return mxServerMap.GetElement(nServerID);
}

NFMapEx<int, ConnectData>& NFCNetClientModule::GetServerList()
{
	return mxServerMap;
}

NFMapEx<int, ConnectData>& NFCNetClientModule::GetServerList(NF_SERVER_TYPES eType)
{
	// TODO: insert return statement here
	return NFMapEx<int, ConnectData>();
}

NF_SHARE_PTR<ConnectData> NFCNetClientModule::GetServerNetInfo(const NFINet * pNet)
{
	int nServerID = 0;
	for (NF_SHARE_PTR<ConnectData> pData = mxServerMap.First(nServerID); pData != NULL; pData = mxServerMap.Next(nServerID))
	{
		if (pData->mxNetModule.get() && pNet == pData->mxNetModule->GetNet())
		{
			return pData;
		}
	}

	return NF_SHARE_PTR<ConnectData>(NULL);
}

void NFCNetClientModule::InitCallBacks(NF_SHARE_PTR<ConnectData> pServerData)
{
	NF_SHARE_PTR<CallBack> xCallBack = mxCallBack.GetElement(pServerData->eServerType);
	if (!xCallBack)
	{
		xCallBack = NF_SHARE_PTR<CallBack>(NF_NEW CallBack);
		mxCallBack.AddElement(pServerData->eServerType, xCallBack);
	}

	//add msg callback
	std::map<int, NET_RECEIVE_FUNCTOR_PTR>::iterator itReciveCB = xCallBack->mxReceiveCallBack.begin();
	for (; xCallBack->mxReceiveCallBack.end() != itReciveCB; ++itReciveCB)
	{
		pServerData->mxNetModule->AddReceiveCallBack(itReciveCB->first, itReciveCB->second);
	}

	//add event callback
	std::list<NET_EVENT_FUNCTOR_PTR>::iterator itEventCB = xCallBack->mxEventCallBack.begin();
	for (; xCallBack->mxEventCallBack.end() != itEventCB; ++itEventCB)
	{
		pServerData->mxNetModule->AddEventCallBack(*itEventCB);
	}

	std::list<NET_RECEIVE_FUNCTOR_PTR>::iterator itCB = xCallBack->mxCallBackList.begin();
	for (; xCallBack->mxCallBackList.end() != itCB; ++itCB)
	{
		pServerData->mxNetModule->AddReceiveCallBack(*itCB);
	}
}

void NFCNetClientModule::ProcessExecute()
{
	NF_SHARE_PTR<ConnectData> pServerData = mxServerMap.First();
	while (pServerData)
	{
		switch (pServerData->eState)
		{
		case ConnectDataState::DISCONNECT:
		{
			if (NULL != pServerData->mxNetModule)
			{
				pServerData->mxNetModule = nullptr;
				pServerData->eState = ConnectDataState::RECONNECT;
			}
		}
		break;
		case ConnectDataState::CONNECTING:
		{
			if (pServerData->mxNetModule)
			{
				pServerData->mxNetModule->Execute();
			}
		}
		break;
		case ConnectDataState::NORMAL:
		{
			if (pServerData->mxNetModule)
			{
				pServerData->mxNetModule->Execute();

				KeepState(pServerData);
			}
		}
		break;
		case ConnectDataState::RECONNECT:
		{
			if ((pServerData->mnLastActionTime + 10) >= GetPluginManager()->GetNowTime())
			{
				break;
			}

			if (nullptr != pServerData->mxNetModule)
			{
				pServerData->mxNetModule = nullptr;
			}

			pServerData->eState = ConnectDataState::CONNECTING;
			pServerData->mxNetModule = NF_SHARE_PTR<NFINetModule>(NF_NEW NFCNetModule(pPluginManager));
			pServerData->mxNetModule->Initialization(pServerData->strIP.c_str(), pServerData->nPort);

			InitCallBacks(pServerData);
		}
		break;
		default:
			break;
		}

		pServerData = mxServerMap.Next();
	}
}

void NFCNetClientModule::LogServerInfo()
{
	LogServerInfo("This is a client, begin to print Server Info----------------------------------");

	ConnectData* pServerData = mxServerMap.FirstNude();
	while (nullptr != pServerData)
	{
		std::ostringstream stream;
		stream << "Type: " << pServerData->eServerType << " ProxyServer ID: " << pServerData->nGameID << " State: " << pServerData->eState << " IP: " << pServerData->strIP << " Port: " << pServerData->nPort;

		LogServerInfo(stream.str());

		pServerData = mxServerMap.NextNude();
	}

	LogServerInfo("This is a client, end to print Server Info----------------------------------");
}
void NFCNetClientModule::KeepState(NF_SHARE_PTR<ConnectData> pServerData)
{
	if (pServerData->mnLastActionTime + 10 > GetPluginManager()->GetNowTime())
	{
		return;
	}

	pServerData->mnLastActionTime = GetPluginManager()->GetNowTime();

	KeepReport(pServerData);
	LogServerInfo();
}

void NFCNetClientModule::OnSocketEvent(const int fd, const NF_NET_EVENT eEvent, NFINet * pNet)
{
	if (eEvent & BEV_EVENT_CONNECTED)
	{
		OnConnected(fd, pNet);
	}
	else
	{
		OnDisConnected(fd, pNet);
	}
}

int NFCNetClientModule::OnConnected(const int fd, NFINet * pNet)
{
	NF_SHARE_PTR<ConnectData> pServerInfo = GetServerNetInfo(pNet);
	if (pServerInfo.get())
	{
		/////////////////////////////////////////////////////////////////////////////////////
		//AddServerWeightData(pServerInfo);
		pServerInfo->eState = ConnectDataState::NORMAL;
	}

	return 0;
}

int NFCNetClientModule::OnDisConnected(const int fd, NFINet * pNet)
{
	NF_SHARE_PTR<ConnectData> pServerInfo = GetServerNetInfo(pNet);
	if (nullptr != pServerInfo)
	{
		/////////////////////////////////////////////////////////////////////////////////////
		//RemoveServerWeightData(pServerInfo);
		pServerInfo->eState = ConnectDataState::DISCONNECT;
		pServerInfo->mnLastActionTime = GetPluginManager()->GetNowTime();
	}

	return 0;
}

void NFCNetClientModule::ProcessAddNetConnect()
{
	std::list<ConnectData>::iterator it = mxTempNetList.begin();
	for (; it != mxTempNetList.end(); ++it)
	{
		const ConnectData& xInfo = *it;
		NF_SHARE_PTR<ConnectData> xServerData = mxServerMap.GetElement(xInfo.nGameID);
		if (nullptr == xServerData)
		{
			xServerData = NF_SHARE_PTR<ConnectData>(NF_NEW ConnectData());

			xServerData->nGameID = xInfo.nGameID;
			xServerData->eServerType = xInfo.eServerType;
			xServerData->strIP = xInfo.strIP;
			xServerData->strName = xInfo.strName;
			xServerData->eState = ConnectDataState::CONNECTING;
			xServerData->nPort = xInfo.nPort;
			xServerData->mnLastActionTime = GetPluginManager()->GetNowTime();

			xServerData->mxNetModule = NF_SHARE_PTR<NFINetModule>(NF_NEW NFCNetModule(pPluginManager));
			xServerData->mxNetModule->Initialization(xServerData->strIP.c_str(), xServerData->nPort);

			InitCallBacks(xServerData);

			mxServerMap.AddElement(xInfo.nGameID, xServerData);
		}
	}

	mxTempNetList.clear();
}