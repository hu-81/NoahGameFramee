// -------------------------------------------------------------------------
//    @FileName         ��    NFIGSSwichServerModule.h
//    @Author           ��    Chuanbo.Guo
//    @Date             ��    2013-07-10
//    @Module           ��    NFIGSSwichServerModule
//
// -------------------------------------------------------------------------

#ifndef _NFI_GSSWICHSERVER_MODULE_H
#define _NFI_GSSWICHSERVER_MODULE_H

#include "NFIModule.h"

class NFIGSSwichServerModule : public NFIModule
{
public:
	virtual bool ChangeServer(const NFGUID& self, const int nServer, const int nSceneID, const int nGroup) = 0;
};

#endif