// -------------------------------------------------------------------------
//    @FileName         :    NFCComponentManager.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2014-02-17
//    @Module           :    NFCComponentManager
//
// -------------------------------------------------------------------------

#ifndef _NFC_COMPONENT_MANAGER_H_
#define _NFC_COMPONENT_MANAGER_H_

#include "NFCComponent.h"
#include "NFIComponentManager.h"
#include "NFIdentID.h"

class NFCComponentManager : public NFIComponentManager
{
public:
    NFCComponentManager(const NFIDENTID& self, NFIPluginManager* pLuginManager)
    {
        mSelf = self;
        m_pPluginManager = pLuginManager;
    }
    
    virtual ~NFCComponentManager()
    {
        DestroyAllComponent();
    }

    virtual bool Init();

    virtual bool AfterInit();

    virtual bool BeforeShut();

    virtual bool Shut();

    virtual bool Execute(const float fLasFrametime, const float fStartedTime);

    virtual NFIComponent* AddComponent(const std::string& strComponentName, const std::string& strScriptName);
    virtual NFIComponent* FindComponent(const std::string& strComponentName);

    virtual bool SetEnable(const std::string& strComponentName, const bool bEnable);

    virtual bool Enable(const std::string& strComponentName);

    virtual NFIDENTID Self();

protected:
    virtual bool DestroyAllComponent();

private:
    NFIDENTID mSelf;
    NFIPluginManager* m_pPluginManager;
};

#endif