// -------------------------------------------------------------------------
//    @FileName     :    NFCGameServerPublicProxyModule.h
//    @Author          :    LvSheng.Huang
//    @Date              :    2013-07-27
//    @Module         :    NFCGameServerPublicProxyModule
//    @Desc             :       ���ᣬ�����У����䣬���У��̳ǣ��̵�ȹ�������ʱ���ݴ���Ĵ������ǽ��ɴ�ת����1�ŷ�����
// -------------------------------------------------------------------------

#ifndef _NFC_GAMESERVER_PUBLICPROXY_MODULE_H_
#define _NFC_GAMESERVER_PUBLICPROXY_MODULE_H_

//  the cause of sock'libariy, thenfore "NFCNet.h" much be included first.

#include "NFComm/NFMessageDefine/NFMsgShare.pb.h"
#include "NFComm/NFPluginModule/NFIGameServerNet_ClientModule.h"
#include "NFComm/NFPluginModule/NFIGameServerNet_ServerModule.h"
#include "NFComm/NFPluginModule/NFIEventProcessModule.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIGameLogicModule.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"

class NFCGameServerPublicProxyModule
{
public:
    //  NFCGameServerPublicProxyModule(NFIPluginManager* p)
    //  {
    //      pPluginManager = p;
    //  }
    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute(const float fLasFrametime, const float fStartedTime);

protected:


private:

    NFIGameServerNet_ServerModule* m_pGameServerModule;
    NFIGameLogicModule* m_pGameLogicModule;
    NFIKernelModule* m_pKernelModule;
    NFIEventProcessModule* m_pEventProcessModule;

};

#endif