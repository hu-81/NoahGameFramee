// -------------------------------------------------------------------------
//    @FileName         :    NFIAccountRedisModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2016-11-07
//    @Module           :    NFIAccountRedisModule
//
// -------------------------------------------------------------------------

#ifndef NFI_ACCOUNT_REDIS_MODULE_H
#define NFI_ACCOUNT_REDIS_MODULE_H

#include "NFIModule.h"

class NFIAccountRedisModule
    : public NFIModule
{

public:
	virtual int VerifyAccount(const std::string& strAccount, const std::string& strPwd) = 0;
};

#endif