// -------------------------------------------------------------------------
//    @FileName      :    NFCCreateRoleModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2013-03-29
//    @Module           :    NFCCreateRoleModule
//
// -------------------------------------------------------------------------

#ifndef NFC_CREATEROLE_MODULE_H
#define NFC_CREATEROLE_MODULE_H

#include "NFComm/NFPluginModule/NFIPluginManager.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIGameLogicModule.h"
#include "NFComm/NFPluginModule/NFIElementModule.h"


class NFCCreateRoleModule
    : public NFIModule
{
public:
    NFCCreateRoleModule(NFIPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual ~NFCCreateRoleModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute(const float fLasFrametime, const float fStartedTime);
    virtual bool AfterInit();

protected:
    static int OnLoadRoleBeginEvent(const NFGUID& object, const int nEventID, const NFIDataList& var);

    static int OnLoadRoleFinalEvent(const NFGUID& object, const int nEventID, const NFIDataList& var);

    static int OnCreateRoleEvent(const NFGUID& object, const int nEventID, const NFIDataList& var);

    static int OnDeleteRoleEvent(const NFGUID& object, const int nEventID, const NFIDataList& var);

    static int OnAcountDisConnectEvent(const NFGUID& object, const int nEventID, const NFIDataList& var);

private:

    //�½��������Ӷ��󣬵ȴ������Լ�����֤KEY��KEY��֤��ɾ��
    //-1
    static int mnConnectContainer;

    //ѡ�˴�������
    //-3
    static int mnRoleHallContainer;

    static NFIGameLogicModule* m_pGameLogicModule;
    static NFIEventProcessModule* m_pEventProcessModule;
    //static NFIDataBaseModule* m_pDataBaseModule;
    static NFIDataNoSqlModule* m_pNoSqlModule;
    static NFIKernelModule* m_pKernelModule;
    static NFIElementInfoModule* m_pElementInfoModule;
    static NFCCreateRoleModule* m_pThis;
};

#endif
