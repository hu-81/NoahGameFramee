// -------------------------------------------------------------------------
//    @FileName			:    NFIPluginManager.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFIPluginManager
//
// -------------------------------------------------------------------------

#ifndef NFI_PLUGIN_MANAGER_H
#define NFI_PLUGIN_MANAGER_H

#include "NFILogicModule.h"

class NFIPlugin;

class NFIPluginManager : public NFILogicModule
{
public:
    NFIPluginManager()
    {

    }

	template <typename T>
	T* FindModule()
	{
		NFILogicModule* pLogicModule = FindModule(typeid(T).name());
		if (pLogicModule)
		{
			if (!TIsDerived<T, NFILogicModule>::Result)
			{
				return NULL;
			}

			T* pT = dynamic_cast<T*>(pLogicModule);
			assert(NULL != pT);

			return pT;
		}

		return NULL;
	}
    virtual void Registered(NFIPlugin* plugin) = 0;

    virtual void UnRegistered(NFIPlugin* plugin) = 0;

    virtual NFIPlugin* FindPlugin(const std::string& strPluginName) = 0;

    virtual void AddModule(const std::string& strModuleName, NFILogicModule* pModule) = 0;

    virtual void RemoveModule(const std::string& strModuleName) = 0;

    virtual NFILogicModule* FindModule(const std::string& strModuleName) = 0;

    virtual int AppID() = 0;
    virtual NFINT64 GetInitTime() const = 0;
    virtual NFINT64 GetNowTime() const = 0;
    virtual const std::string& GetConfigPath() const = 0;
};

#endif
