// NFLoginNet_ServerPlugin.cpp : Defines the exported functions for the DLL application.
//

#include "NFMasterNet_HttpServerPlugin.h"
#include "NFCMasterNet_HttpServerModule.h"
#include "NFCMasterNet_WebServerModule.h"
//
//
#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(NFIPluginManager* pm)
{

	CREATE_PLUGIN(pm, NFMasterNet_HttpServerPlugin)

};

NF_EXPORT void DllStopPlugin(NFIPluginManager* pm)
{
	DESTROY_PLUGIN(pm, NFMasterNet_HttpServerPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int NFMasterNet_HttpServerPlugin::GetPluginVersion()
{
	return 0;
}

const std::string NFMasterNet_HttpServerPlugin::GetPluginName()
{
	return GET_CLASS_NAME(NFMasterNet_HttpServerPlugin)
}

void NFMasterNet_HttpServerPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, NFIMasterNet_JsonServerModule, NFCMasterNet_HttpJsonModule)
	REGISTER_MODULE(pPluginManager, NFIMasterNet_WebServerModule, NFCMasterNet_WebServerModule)
}

void NFMasterNet_HttpServerPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, NFIMasterNet_WebServerModule, NFCMasterNet_WebServerModule)
	UNREGISTER_MODULE(pPluginManager, NFIMasterNet_JsonServerModule, NFCMasterNet_HttpJsonModule)
}