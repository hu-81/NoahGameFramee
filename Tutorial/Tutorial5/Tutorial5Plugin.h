// -------------------------------------------------------------------------
//    @FileName      :    NFTutorial6.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2014-05-14 08:51
//    @Module           :   NFTutorial6
//
// -------------------------------------------------------------------------

#ifndef _NF_TUTORIAL5_H_
#define _NF_TUTORIAL5_H_

///
#include "NFComm/NFPluginModule/NFIPlugin.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"

class Tutorial5Plugin : public NFIPlugin
{
public:
    Tutorial5Plugin(NFIPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif