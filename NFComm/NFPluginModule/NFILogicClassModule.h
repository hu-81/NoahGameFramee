// -------------------------------------------------------------------------
//    @FileName         :    NFILogicClassModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFILogicClassModule
//
// -------------------------------------------------------------------------

#ifndef _NFI_LOGICCLASS_MODULE_H_
#define _NFI_LOGICCLASS_MODULE_H_

#include <iostream>
#include "NFILogicModule.h"
#include "NFComm/NFCore/NFIPropertyManager.h"
#include "NFComm/NFCore/NFIRecordManager.h"
#include "NFComm/NFCore/NFIComponentManager.h"

class NFILogicClass
    : public NFList<std::string>//include files
{
public:
    virtual ~NFILogicClass(){}

    virtual std::shared_ptr<NFIPropertyManager> GetPropertyManager() = 0;

    virtual std::shared_ptr<NFIRecordManager> GetRecordManager() = 0;

    virtual std::shared_ptr<NFIComponentManager> GetComponentManager() = 0;

    virtual void SetParent(std::shared_ptr<NFILogicClass> pClass) = 0;
    virtual std::shared_ptr<NFILogicClass> GetParent() = 0;
    virtual void SetTypeName(const char* strType) = 0;
    virtual const std::string& GetTypeName() = 0;
    virtual const std::string& GetClassName() = 0;
    virtual const bool AddConfigName(std::string& strConfigName) = 0;
    virtual NFList<std::string>& GetConfigNameList() = 0;
    virtual void SetInstancePath(const std::string& strPath) = 0;
    virtual const std::string& GetInstancePath() = 0;
};

class NFILogicClassModule
    : public NFILogicModule,
      public NFMapEx<std::string, NFILogicClass>
{
public:
    virtual ~NFILogicClassModule() {}
	virtual bool Load() = 0;
	virtual bool Save() = 0;
	virtual bool Clear() = 0;

    virtual std::shared_ptr<NFIPropertyManager> GetClassPropertyManager(const std::string& strClassName) = 0;

    virtual std::shared_ptr<NFIRecordManager> GetClassRecordManager(const std::string& strClassName) = 0;

    virtual std::shared_ptr<NFIComponentManager> GetClassComponentManager(const std::string& strClassName) = 0;

};

#endif