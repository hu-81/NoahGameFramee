// -------------------------------------------------------------------------
//    @FileName         ��    NFIGameServerToWorldModule.h
//    @Author           ��    LvSheng.Huang
//    @Date             ��    2012-12-15
//    @Module           ��    NFIGameServerToWorldModule
//
// -------------------------------------------------------------------------

#ifndef NFI_GAMESERVERTOWORLDMODULE_H
#define NFI_GAMESERVERTOWORLDMODULE_H

#include <iostream>
#include "NFILogicModule.h"
#include "NFIClusterClientModule.hpp"

class NFIGameServerToWorldModule
    : public NFILogicModule
{

public:
	virtual void SendBySuit(const int& nHashKey, const int nMsgID, const char* msg, const uint32_t nLen) = 0;
    virtual NFIClusterClientModule* GetClusterClientModule() = 0;
};

#endif