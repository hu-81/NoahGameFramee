// -------------------------------------------------------------------------
//    @FileName			:    NFCMasterNet_ServerModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2013-01-02
//    @Module           :    NFCMasterNet_ServerModule
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef NFC_MASTERNET_SERVER_MODULE_H
#define NFC_MASTERNET_SERVER_MODULE_H

//  the cause of sock'libariy, thenfore "NFCNet.h" much be included first.

#include "NFComm/NFMessageDefine/NFMsgDefine.h"
#include "NFComm/NFPluginModule/NFIMasterNet_ServerModule.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFILogModule.h"
#include "NFComm/NFPluginModule/NFINetModule.h"
#include "NFComm/NFPluginModule/NFIClassModule.h"
#include "NFComm/NFPluginModule/NFIElementModule.h"

class NFCMasterNet_ServerModule
    : public NFIMasterNet_ServerModule
{
public:
    NFCMasterNet_ServerModule(NFIPluginManager* p)
    {
		pPluginManager = p;
        mnLastLogTime = pPluginManager->GetNowTime();
    }
	virtual ~NFCMasterNet_ServerModule();

    virtual bool Init();
    virtual bool Shut();

    virtual bool AfterInit();
    virtual bool Execute();

    virtual void LogReceive(const char* str) {}
    virtual void LogSend(const char* str) {}

	virtual std::string GetServersStatus();

protected:

    void OnSocketEvent(const int nSockIndex, const NF_NET_EVENT eEvent, NFINet* pNet);
    void OnClientDisconnect(const int nAddress);
    void OnClientConnected(const int nAddress);

protected:
    void OnWorldRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);
    void OnWorldUnRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);
    void OnRefreshWorldInfoProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);

    //////////////////////////////////////////////////////////////////////////
    void OnLoginRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);
    void OnLoginUnRegisteredProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);
    void OnRefreshLoginInfoProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);

    void OnSelectWorldProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);
    void OnSelectServerResultProcess(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);

	void OnServerReport(const int nFd, const int msgId, const char* buffer, const uint32_t nLen);

    //////////////////////////////////////////////////////////////////////////

    void SynWorldToLogin();
    void LogGameServer();

	void OnHeartBeat(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);
	void InvalidMessage(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen);

private:

    NFINT64 mnLastLogTime;

    //serverid,data
	NFMapEx<int, ServerData> mMasterMap;
	NFMapEx<int, ServerData> mLoginMap;
    NFMapEx<int, ServerData> mWorldMap;
	NFMapEx<int, ServerData> mProxyMap;
	NFMapEx<int, ServerData> mGameMap;


    NFIElementModule* m_pElementModule;
    NFIClassModule* m_pClassModule;
    NFIKernelModule* m_pKernelModule;
    NFILogModule* m_pLogModule;
	NFINetModule* m_pNetModule;
};

#endif