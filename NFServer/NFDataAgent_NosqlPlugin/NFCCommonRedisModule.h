// -------------------------------------------------------------------------
//    @FileName			:    NFCRankRedisModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2013-10-03
//    @Module           :    NFCRankRedisModule
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef NFC_COMMON_REDIS_MODULE_H
#define NFC_COMMON_REDIS_MODULE_H

#include "NFComm/NFMessageDefine/NFMsgDefine.h"
#include "NFComm/NFPluginModule/NFIClassModule.h"
#include "NFComm/NFPluginModule/NFILogModule.h"
#include "NFComm/NFPluginModule/NFIElementModule.h"
#include "NFComm/NFPluginModule/NFICommonRedisModule.h"
#include "NFComm/NFPluginModule/NFINoSqlModule.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"

class NFCCommonRedisModule : public NFICommonRedisModule
{
public:
    NFCCommonRedisModule(NFIPluginManager* p);

    virtual bool AfterInit();

public:
    virtual std::string GetPropertyCacheKey(const NFGUID& self);
	virtual std::string GetRecordCacheKey(const NFGUID& self);
	virtual std::string GetPropertyStorageKey(const NFGUID& self);
	virtual std::string GetRecordStorageKey(const NFGUID& self);

	virtual std::string GetAccountCacheKey(const std::string& strAccount);
	virtual std::string GetTileCacheKey(const NFGUID& self);

    virtual NF_SHARE_PTR<NFIPropertyManager> NewPropertyManager(const NFGUID& self);
    virtual NF_SHARE_PTR<NFIRecordManager> NewRecordManager(const NFGUID& self);

    virtual NF_SHARE_PTR<NFIPropertyManager> GetCachePropertyInfo(const NFGUID& self);
    virtual NF_SHARE_PTR<NFIRecordManager> GetCacheRecordInfo(const NFGUID& self);

	virtual bool GetCachePropertyListPB(const NFGUID& self, NFMsg::ObjectPropertyList& propertyList);
	virtual bool GetCacheRecordListPB(const NFGUID& self, NFMsg::ObjectRecordList& recordList);

	virtual bool GetStoragePropertyListPB(const NFGUID& self, NFMsg::ObjectPropertyList& propertyList);
	virtual bool GetStorageRecordListPB(const NFGUID& self, NFMsg::ObjectRecordList& recordList);

    virtual bool SetCachePropertyInfo(const NFGUID& self, NF_SHARE_PTR<NFIPropertyManager> pPropertyManager);
    virtual bool SetCacheRecordInfo(const NFGUID& self, NF_SHARE_PTR<NFIRecordManager> pRecordManager);

	virtual bool SetStroragePropertyInfo(const NFGUID& self, NF_SHARE_PTR<NFIPropertyManager> pPropertyManager);
	virtual bool SetStrorageRecordInfo(const NFGUID& self, NF_SHARE_PTR<NFIRecordManager> pRecordManager);

    virtual bool RemoveCachePropertyInfo(const NFGUID& self);
    virtual bool RemoveCacheRecordInfo(const NFGUID& self);

    virtual bool ConvertPBToPropertyManager(const NFMsg::ObjectPropertyList& xMsg, NF_SHARE_PTR<NFIPropertyManager>& pPropertyManager, const bool bCache);
    virtual bool ConvertPBToRecordManager(const NFMsg::ObjectRecordList& xMsg, NF_SHARE_PTR<NFIRecordManager>& pRecordManager, const bool bCache);

    virtual bool ConvertPropertyManagerToPB(const NF_SHARE_PTR<NFIPropertyManager>& pPropertyManager, NFMsg::ObjectPropertyList& xMsg, const bool bCache);
    virtual bool ConvertRecordManagerToPB(const NF_SHARE_PTR<NFIRecordManager>& pRecordManager, NFMsg::ObjectRecordList& xMsg, const bool bCache);

protected:
	NFIKernelModule* m_pKernelModule;
	NFIClassModule* m_pLogicClassModule;
    NFINoSqlModule* m_pNoSqlModule;
	NFIElementModule* m_pElementModule;
	NFILogModule* m_pLogModule;
};


#endif
