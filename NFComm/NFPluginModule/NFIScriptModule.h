// -------------------------------------------------------------------------
//    @FileName         ：    NFIScriptModule.h
//    @Author           ：    LvSheng.Huang
//    @Date             ：    2013-07-08
//    @Module           ：    NFIScriptModule
//    @Desc             :     every script plugin need to export two interfaces(NFCScriptVarList and most of NFCScriptKernel)
// -------------------------------------------------------------------------

#ifndef _NFI_SCRIPT_MODULE_H_
#define _NFI_SCRIPT_MODULE_H_

#include <iostream>
#include "NFILogicModule.h"
#include "NFComm/NFCore/NFCDataList.h"
#include "NFComm/NFPluginModule/NFIdentID.h"
#include "NFComm/NFPluginModule/NFIElementInfoModule.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIScriptKernelModule.h"
#include "NFComm/NFPluginModule/NFILogicClassModule.h"
#include "NFComm/NFPluginModule/NFIEventProcessModule.h"
#include "NFComm/NFPluginModule/NFILuaScriptModule.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"

class NFCScriptName
{
public:
    bool operator < (const NFCScriptName& id) const
    {
        return this->strComponentName.length() < id.strComponentName.length() && this->strFunctionName.length() < id.strFunctionName.length();
    }

    bool operator == (const NFCScriptName& id) const
    {
        if (this->strComponentName != id.strComponentName
            || this->strFunctionName != id.strFunctionName)
        {
            return false;
        }

        return true;
    }

    NFCScriptName(){}

    NFCScriptName(const std::string& strComponentName, const std::string& strFunctionName)
    {
        this->strComponentName = strComponentName;
        this->strFunctionName = strFunctionName;
    }

    std::string strComponentName;
    std::string strFunctionName;
};


class NFCSriptData
{
public:
    //eventlist: id->ScriptName,FunctionName
    NFMap<int, NFList<NFCScriptName>> mxEventData;

    //heartbeatlist: name->ScriptName,FunctionName
    NFMap<std::string, NFList<NFCScriptName>> mxHeartBeatData;

    //propertycblist: name->ScriptName,FunctionName
    NFMap<std::string, NFList<NFCScriptName>> mxPropertyCallBackData;

    //recordcblist: name->ScriptName,FunctionName
    NFMap<std::string, NFList<NFCScriptName>> mxRecordCallBackData;

protected:
private:
};

class NFIScriptModule
    : public NFILogicModule, public NFMap<NFIDENTID, NFCSriptData>
{

public:
    virtual int DoHeartBeatCommonCB(const NFIDENTID& self, const std::string& strHeartBeat, const float fTime, const int nCount)
    {
        NFCSriptData* pScriptData = GetElement(self);
        if (pScriptData)
        {
            NFList<NFCScriptName>* pList = pScriptData->mxHeartBeatData.GetElement(strHeartBeat);
            if (pList)
            {
                NFCScriptName xScriptName;
                bool bRet = pList->First(xScriptName);
                while (bRet)
                {
                    DoHeartBeatScript(self, strHeartBeat, fTime, nCount, xScriptName.strComponentName, xScriptName.strFunctionName);

                    bRet = pList->Next(xScriptName);
                }
            }
        }
        return 0;
    }

    virtual int DoEventCommonCB(const NFIDENTID& self, const int nEventID, const NFIDataList& var)
    {
        NFCSriptData* pScriptData = GetElement(self);
        if (pScriptData)
        {
            NFList<NFCScriptName>* pList = pScriptData->mxEventData.GetElement(nEventID);
            if (pList)
            {
                NFCScriptName xScriptName;
                bool bRet = pList->First(xScriptName);
                while (bRet)
                {
                    DoEventScript(self, nEventID, xScriptName.strComponentName, xScriptName.strFunctionName, var);

                    bRet = pList->Next(xScriptName);
                }
            }
        }

        return 0;
    }

    virtual int DoPropertyCommEvent(const NFIDENTID& self, const std::string& strPropertyName, const NFIDataList& oldVar, const NFIDataList& newVar)
    {
        NFCSriptData* pScriptData = GetElement(self);
        if (pScriptData)
        {
            NFList<NFCScriptName>* pList = pScriptData->mxPropertyCallBackData.GetElement(strPropertyName);
            if (pList)
            {
                NFCScriptName xScriptName;
                bool bRet = pList->First(xScriptName);
                while (bRet)
                {
                    DoScriptPropertyCallBack(self, strPropertyName, xScriptName.strComponentName, xScriptName.strFunctionName, oldVar, newVar);

                    bRet = pList->Next(xScriptName);
                }
            }
        }

        return 0;
    }

    virtual int DoRecordCommonEvent(const NFIDENTID& self, const RECORD_EVENT_DATA& xEventData, const NFIDataList& oldVar, const NFIDataList& newVar)
    {
        NFCSriptData* pScriptData = GetElement(self);
        if (pScriptData)
        {
            NFList<NFCScriptName>* pList = pScriptData->mxRecordCallBackData.GetElement(xEventData.strRecordName);
            if (pList)
            {
                NFCScriptName xScriptName;
                bool bRet = pList->First(xScriptName);
                while (bRet)
                {
                    DoScriptRecordCallBack(self, xEventData.strRecordName, xScriptName.strComponentName, xScriptName.strFunctionName, xEventData.nOpType, xEventData.nRow, xEventData.nCol, oldVar, newVar);

                    bRet = pList->Next(xScriptName);
                }
            }
        }

        return 0;
    }

    virtual int DoClassCommonEvent(NFILogicClassModule* pLogicClassModule, const NFIDENTID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList& var)
    {
        std::string strSerializationName;

        switch (eClassEvent)
        {
        case COE_CREATE_NODATA:
            strSerializationName = "Init";
            break;

        case COE_CREATE_HASDATA:
            strSerializationName = "AfterInit";
            break;

        case COE_BEFOREDESTROY:
            strSerializationName = "BeforeShut";
            break;

        case COE_DESTROY:
            strSerializationName = "Shut";
            break;

        default:
            break;
        }

        if (!strSerializationName.empty())
        {
            NF_SHARE_PTR<NFIComponentManager> pComponentManager = pLogicClassModule->GetClassComponentManager(strClassName);
            if (pComponentManager.get())
            {
                NF_SHARE_PTR<NFIComponent> pComponent = pComponentManager->First();
                while (pComponent.get() && pComponent->Enable())
                {
                    DoScript(self, pComponent->ComponentName(), strSerializationName, var);

                    pComponent = pComponentManager->Next();
                }
            }
        }

        return 0;
    }

    //call script
    virtual int DoScript(const NFIDENTID& self, const std::string& strComponentName, const std::string& strFunction, const NFCDataList& arg) = 0;
    virtual int DoEventScript(const NFIDENTID& self, const int nEventID, const std::string& strComponentName, const std::string& strFunction, const NFCDataList& arg) = 0;
    virtual int DoHeartBeatScript(const NFIDENTID& self, const std::string& strHeartBeat, const float fTime, const int nCount, std::string& strComponentName, const std::string& strFunction) = 0;

    virtual int DoScriptPropertyCallBack(const NFIDENTID& self, const std::string& strPropertyName, const std::string& strComponentName, const std::string& strFunction, const NFCDataList& oldVar, const NFCDataList& newVar) = 0;
    virtual int DoScriptRecordCallBack(const NFIDENTID& self, const std::string& strRecordName, const std::string& strComponentName, const std::string& strFunction, const int nOpType, const int nRow, const int nCol, const NFCDataList& oldVar, const NFCDataList& newVar) = 0;

    // operating function
    virtual bool AddPropertyCallBack(const NFIDENTID& self, const std::string& strPropertyName, const std::string& strComponentName, const std::string& strFunction)
    {
        NFCSriptData* pScriptData = GetElement(self);
        if (!pScriptData)
        {
            pScriptData = new NFCSriptData();
            AddElement(self, pScriptData);
        }

        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxPropertyCallBackData.GetElement(strPropertyName);
        if (!pScriptNameList)
        {
            pScriptNameList = new NFList<NFCScriptName>();
            pScriptData->mxPropertyCallBackData.AddElement(strPropertyName, pScriptNameList);
        }

        NFCScriptName xScriptName(strComponentName, strFunction);
        pScriptNameList->Add(xScriptName);

        NFIKernelModule* pKernelModule = dynamic_cast<NFIKernelModule*>(GetPluginManager()->FindModule("NFCKernelModule"));
        pKernelModule->AddPropertyCallBack(self, strPropertyName, this, &NFIScriptModule::OnPropertyCB);

        return true;
    }

    int OnPropertyCB(const NFIDENTID& self, const std::string& strPropertyName, const NFIDataList& oldVar, const NFIDataList& newVar)
    {
        return DoPropertyCommEvent(self, strPropertyName, oldVar, newVar);
    }

    virtual bool AddRecordCallBack(const NFIDENTID& self, const std::string& strRecordName, const std::string& strComponentName, const std::string& strFunction)
    {
        NFCSriptData* pScriptData = GetElement(self);
        if (!pScriptData)
        {
            pScriptData = new NFCSriptData();
            AddElement(self, pScriptData);
        }

        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxRecordCallBackData.GetElement(strRecordName);
        if (!pScriptNameList)
        {
            pScriptNameList = new NFList<NFCScriptName>();
            pScriptData->mxRecordCallBackData.AddElement(strRecordName, pScriptNameList);
        }

        NFCScriptName xScriptName(strComponentName, strFunction);
        pScriptNameList->Add(xScriptName);

        NFIKernelModule* pKernelModule = dynamic_cast<NFIKernelModule*>(GetPluginManager()->FindModule("NFCKernelModule"));
        pKernelModule->AddRecordCallBack(self, strRecordName, this, &NFIScriptModule::OnRecordCB);

        return true;
    }

    int OnRecordCB(const NFIDENTID& self, const RECORD_EVENT_DATA& xEventData, const NFIDataList& oldVar, const NFIDataList& newVar)
    {
        return DoRecordCommonEvent(self, xEventData, oldVar, newVar);
    }

    virtual bool AddHeartBeatCallBack(const NFIDENTID& self, const std::string& strHeartBeatName, const std::string& strComponentName, const std::string& strFunction, const float fTime, const int nCount)
    {
        NFCSriptData* pScriptData = GetElement(self);
        if (!pScriptData)
        {
            pScriptData = new NFCSriptData();
            AddElement(self, pScriptData);
        }

        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxHeartBeatData.GetElement(strHeartBeatName);
        if (!pScriptNameList)
        {
            pScriptNameList = new NFList<NFCScriptName>();
            pScriptData->mxHeartBeatData.AddElement(strHeartBeatName, pScriptNameList);
        }

        //应该是同时直接向系统注册.
        NFCScriptName xScriptName(strComponentName, strFunction);
        pScriptNameList->Add(xScriptName);

        NFIKernelModule* pKernelModule = dynamic_cast<NFIKernelModule*>(GetPluginManager()->FindModule("NFCKernelModule"));
        pKernelModule->AddHeartBeat(self, strHeartBeatName, this, &NFIScriptModule::OnHeartBeatCB, fTime, nCount);

        return true;
    }

    int OnHeartBeatCB(const NFIDENTID& self, const std::string& strHeartBeatName, const float fTime, const int nCount)
    {
        return DoHeartBeatCommonCB(self, strHeartBeatName, fTime, nCount);
    }

    virtual bool AddEventCallBack(const NFIDENTID& self, const int nEventID, const std::string& strComponentName, const std::string& strFunction)
    {
        NFCSriptData* pScriptData = GetElement(self);
        if (!pScriptData)
        {
            pScriptData = new NFCSriptData();
            AddElement(self, pScriptData);
        }

        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxEventData.GetElement(nEventID);
        if (!pScriptNameList)
        {
            pScriptNameList = new NFList<NFCScriptName>();
            pScriptData->mxEventData.AddElement(nEventID, pScriptNameList);
        }

        NFCScriptName xScriptName(strComponentName, strFunction);
        pScriptNameList->Add(xScriptName);

        NFIKernelModule* pKernelModule = dynamic_cast<NFIKernelModule*>(GetPluginManager()->FindModule("NFCKernelModule"));
        pKernelModule->AddEventCallBack(self, nEventID, this, &NFIScriptModule::OnEventCB);

        return true;
    }

    int OnEventCB(const NFIDENTID& self, const int nEventID, const NFIDataList& argVar)
    {
        return DoEventCommonCB(self, nEventID, argVar);
    }
};

//class NFCScriptKernelModule : public NFIScriptKernelModule
//{
//public:
//    NFCScriptKernelModule(NFIKernelModule* pKernelModule, NFIScriptModule* pScriptModule, NFIElementInfoModule* pElementInfoModule, NFIEventProcessModule* pEventProcessModule)
//    {
//        m_pKernelModule = pKernelModule;
//        m_pScriptModule = pScriptModule;
//        m_pElementInfoModule = pElementInfoModule;
//        m_pEventProcessModule = pEventProcessModule;
//    }
//
//    //be called from script
//    ///////need to export function///////////////////////////////////
//    bool HasEventCallBack(const NFIDENTID& objectID, const int nEventID)
//    {
//        NFCSriptData* pScriptData = GetElement(objectID);
//        if (pScriptData)
//        {
//            if(pScriptData->mxEventData.GetElement(nEventID))
//            {
//                return true;
//            }
//        }
//
//        return false;
//    }
//
//    bool RemoveEvent(const NFIDENTID& objectID)
//    {
//        NFCSriptData* pScriptData = RemoveElement(objectID);
//        if (pScriptData)
//        {
//            NFList<NFCScriptName>* pScriptNameList = pScriptData->mxEventData.First();
//            while (pScriptNameList)
//            {
//                delete pScriptNameList;
//                pScriptNameList = NULL;
//
//                pScriptNameList = pScriptData->mxEventData.Next();
//            }
//
//            pScriptData->mxEventData.ClearAll();
//
//            delete pScriptData;
//            pScriptData = NULL;
//
//            return true;
//        }
//
//        return false;
//    }
//
//    bool RemoveEventCallBack(const NFIDENTID& objectID, const int nEventID)
//    {
//        NFCSriptData* pScriptData = GetElement(objectID);
//        if (pScriptData)
//        {
//            int nEventID = 0;
//            NFList<NFCScriptName>* pScriptNameList = pScriptData->mxEventData.RemoveElement(nEventID);
//            if (pScriptNameList)
//            {
//                delete pScriptNameList;
//                pScriptNameList = NULL;
//
//                return true;
//            }
//        }
//
//        return false;
//    }
//
//    bool DoEvent(const NFIDENTID& objectID, const int nEventID, const NFCScriptVarList& valueList)
//    {
//        //do c++ event
//        return m_pEventProcessModule->DoEvent(objectID, nEventID, valueList.GetVar());
//    }
//
//    bool ExistElement(const std::string& strConfigName)
//    {
//        return m_pElementInfoModule->ExistElement(strConfigName);
//    }
//
//    int GetPropertyInt(const std::string& strConfigName, const std::string& strPropertyName)
//    {
//        return m_pElementInfoModule->GetPropertyInt(strConfigName, strPropertyName);
//    }
//
//    float GetPropertyFloat(const std::string& strConfigName, const std::string& strPropertyName)
//    {
//        return m_pElementInfoModule->GetPropertyFloat(strConfigName, strPropertyName);
//    }
//
//    const std::string& GetPropertyString(const std::string& strConfigName, const std::string& strPropertyName)
//    {
//        return m_pElementInfoModule->GetPropertyString(strConfigName, strPropertyName);
//    }
//    //////////////////////////////////////////////////////////////////
//
//
//    bool AddPropertyCallBack(const NFIDENTID& self, const std::string& strPropertyName, const std::string& strComponentName, const std::string& strFunction)
//    {
//        NFCSriptData* pScriptData = GetElement(self);
//        if (!pScriptData)
//        {
//            pScriptData = new NFCSriptData();
//            AddElement(self, pScriptData);
//        }
//
//        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxPropertyCallBackData.GetElement(strPropertyName);
//        if (!pScriptNameList)
//        {
//            pScriptNameList = new NFList<NFCScriptName>();
//            pScriptData->mxPropertyCallBackData.AddElement(strPropertyName, pScriptNameList);
//        }
//
//        NFCScriptName xScriptName(strComponentName, strFunction);
//        return pScriptNameList->Add(xScriptName);
//
//        return false;
//    }
//
//    bool AddRecordCallBack(const NFIDENTID& self, const std::string& strRecordName, const std::string& strComponentName, const std::string& strFunction)
//    {
//        NFCSriptData* pScriptData = GetElement(self);
//        if (!pScriptData)
//        {
//            pScriptData = new NFCSriptData();
//            AddElement(self, pScriptData);
//        }
//
//        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxRecordCallBackData.GetElement(strRecordName);
//        if (!pScriptNameList)
//        {
//            pScriptNameList = new NFList<NFCScriptName>();
//            pScriptData->mxRecordCallBackData.AddElement(strRecordName, pScriptNameList);
//        }
//
//        NFCScriptName xScriptName(strComponentName, strFunction);
//        return pScriptNameList->Add(xScriptName);
//
//        return false;
//    }
//
//    bool AddEventCallBack(const NFIDENTID& self, const int nEventID, const std::string& strComponentName, const std::string& strFunction)
//    {
//        NFCSriptData* pScriptData = GetElement(self);
//        if (!pScriptData)
//        {
//            pScriptData = new NFCSriptData();
//            AddElement(self, pScriptData);
//        }
//
//        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxEventData.GetElement(nEventID);
//        if (!pScriptNameList)
//        {
//            pScriptNameList = new NFList<NFCScriptName>();
//            pScriptData->mxEventData.AddElement(nEventID, pScriptNameList);
//        }
//
//        NFCScriptName xScriptName(strComponentName, strFunction);
//        pScriptNameList->Add(xScriptName);
//
//        m_pKernelModule->AddEventCallBack(self, nEventID, this, &NFCScriptKernelModule::OnEventCommonCB);
//
//        return true;
//    }
//
//    int OnEventCommonCB(const NFIDENTID& self, const int nEventID, const NFIDataList& var)
//    {
//        m_pScriptModule->DoEventCommonCB(this, self, nEventID, var);
//        return 0;
//    }
//
//    bool AddHeartBeat(const NFIDENTID self, const std::string& strHeartBeatName, const std::string& strComponentName, const std::string& strFunction, const float fTime, const int nCount)
//    {
//        NFCSriptData* pScriptData = GetElement(self);
//        if (!pScriptData)
//        {
//            pScriptData = new NFCSriptData();
//            AddElement(self, pScriptData);
//        }
//
//        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxHeartBeatData.GetElement(strHeartBeatName);
//        if (!pScriptNameList)
//        {
//            pScriptNameList = new NFList<NFCScriptName>();
//            pScriptData->mxHeartBeatData.AddElement(strHeartBeatName, pScriptNameList);
//        }
//
//        //应该是同时直接向系统注册.
//        NFCScriptName xScriptName(strComponentName, strFunction);
//        pScriptNameList->Add(xScriptName);
//
//        m_pKernelModule->AddHeartBeat(self, strHeartBeatName, this, &NFCScriptKernelModule::OnHeartBeatCommonCB, fTime, nCount);
//
//        return true;
//    }
//
//    int OnHeartBeatCommonCB(const NFIDENTID& self, const std::string& strHeartBeat, const float fTime, const int nCount)
//    {
//        m_pScriptModule->DoHeartBeatCommonCB(this, self, strHeartBeat, fTime, nCount);
//        return 0;
//    }
//
//    bool FindHeartBeat(const NFIDENTID& self, const std::string& strHeartBeatName)
//    {
//        NFCSriptData* pScriptData = GetElement(self);
//        if (!pScriptData)
//        {
//            return false;
//        }
//
//        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxHeartBeatData.GetElement(strHeartBeatName);
//        if (!pScriptNameList)
//        {
//            return false;
//        }
//
//        return true;
//    }
//
//    bool RemoveHeartBeat(const NFIDENTID& self, const std::string& strHeartBeatName)
//    {
//        NFCSriptData* pScriptData = GetElement(self);
//        if (!pScriptData)
//        {
//            return false;
//        }
//
//        NFList<NFCScriptName>* pScriptNameList = pScriptData->mxHeartBeatData.RemoveElement(strHeartBeatName);
//        if (!pScriptNameList)
//        {
//            delete pScriptNameList;
//            pScriptNameList = NULL;
//
//            return true;
//        }
//
//        return false;
//    }
//
//    //////////////////////////////////////////////////////////////////
//    bool SetComponentEnable(const NFIDENTID& self, const std::string& strComponentName, const bool bEnable)
//    {
//        return m_pKernelModule->SetComponentEnable(self, strComponentName, bEnable);
//    }
//
//    bool QueryComponentEnable(const NFIDENTID& self, const std::string& strComponentName)
//    {
//        return m_pKernelModule->QueryComponentEnable(self, strComponentName);
//    }
//
//    bool CreateContainer(const int nContainerIndex, const std::string& strSceneConfigID)
//    {
//        return m_pKernelModule->CreateContainer(nContainerIndex, strSceneConfigID);
//    }
//
//    bool ExistContainer(const int nContainerIndex)
//    {
//        return m_pKernelModule->ExistContainer(nContainerIndex);
//    }
//
//    bool CreateObject(const NFIDENTID& self, const int nContainerID, const int nGroupID, const std::string& strClassName, const std::string& strConfigIndex, const NFCScriptVarList& arg)
//    {
//        NF_SHARE_PTR<NFIObject> pObject = m_pKernelModule->CreateObject(self, nContainerID, nGroupID, strClassName, strConfigIndex, arg.GetVar());
//        if (pObject.get())
//        {
//            return true;
//        }
//
//        return false;
//    }
//
//    bool DestroyObject(const NFIDENTID& self)
//    {
//        return m_pKernelModule->DestroyObject(self);
//    }
//
//    bool FindProperty(const NFIDENTID& self, const std::string& strPropertyName)
//    {
//        return m_pKernelModule->FindProperty(self, strPropertyName);
//    }
//
//    bool SetPropertyInt(const NFIDENTID& self, const std::string& strPropertyName, const int nValue)
//    {
//        return m_pKernelModule->SetPropertyInt(self, strPropertyName, nValue);
//    }
//
//    bool SetPropertyFloat(const NFIDENTID& self, const std::string& strPropertyName,  const float fValue)
//    {
//        return m_pKernelModule->SetPropertyFloat(self, strPropertyName, fValue);
//    }
//
//    bool SetPropertyString(const NFIDENTID& self, const std::string& strPropertyName, const std::string& strValue)
//    {
//        return m_pKernelModule->SetPropertyString(self, strPropertyName, strValue);
//    }
//
//    bool SetPropertyObject(const NFIDENTID& self, const std::string& strPropertyName, const NFIDENTID& objectValue)
//    {
//        return m_pKernelModule->SetPropertyObject(self, strPropertyName, objectValue);
//    }
//
//    int GetPropertyInt(const NFIDENTID& self, const std::string& strPropertyName)
//    {
//        return m_pKernelModule->GetPropertyInt(self, strPropertyName);
//    }
//
//    float GetPropertyFloat(const NFIDENTID& self, const std::string& strPropertyName)
//    {
//        return m_pKernelModule->GetPropertyFloat(self, strPropertyName);
//    }
//
//    const std::string& GetPropertyString(const NFIDENTID& self, const std::string& strPropertyName)
//    {
//        return m_pKernelModule->GetPropertyString(self, strPropertyName);
//    }
//
//    NFIDENTID GetPropertyObject(const NFIDENTID& self, const std::string& strPropertyName)
//    {
//        return m_pKernelModule->GetPropertyObject(self, strPropertyName);
//    }
//
//    bool SetRecordInt(const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol, const int nValue)
//    {
//        return m_pKernelModule->SetRecordInt(self, strRecordName, nRow, nCol, nValue);
//    }
//
//    bool SetRecordFloat(const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol,  const float fValue)
//    {
//        return m_pKernelModule->SetRecordFloat(self, strRecordName, nRow, nCol, fValue);
//    }
//
//    bool SetRecordString(const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol, const std::string& strValue)
//    {
//        return m_pKernelModule->SetRecordString(self, strRecordName, nRow, nCol, strValue);
//    }
//
//    bool SetRecordObject(const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol, const NFIDENTID& objectValue)
//    {
//        return m_pKernelModule->SetRecordObject(self, strRecordName, nRow, nCol, objectValue);
//    }
//
//    int GetRecordInt(const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
//    {
//        return m_pKernelModule->GetRecordInt(self, strRecordName, nRow, nCol);
//    }
//
//    float GetRecordFloat(const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
//    {
//
//        return m_pKernelModule->GetRecordFloat(self, strRecordName, nRow, nCol);
//    }
//
//    const std::string& GetRecordString(const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
//    {
//        return m_pKernelModule->GetRecordString(self, strRecordName, nRow, nCol);
//    }
//
//    NFIDENTID GetRecordObject(const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
//    {
//        return m_pKernelModule->GetRecordObject(self, strRecordName, nRow, nCol);
//    }
//
//    bool AddProperty(const NFIDENTID& self, const std::string& strPropertyName, const TDATA_TYPE varType, bool bPublic ,  bool bPrivate ,  bool bSave, bool bView, int nIndex, const std::string& strScriptFunction)
//    {
//        return m_pKernelModule->AddProperty(self, strPropertyName, varType, bPublic, bPrivate, bSave, bView, nIndex, strScriptFunction);
//    }
//
//    bool AddRow(const NFIDENTID& self, const std::string& strRecordName, const NFIDataList& var)
//    {
//        NF_SHARE_PTR<NFIRecord> pRecord = m_pKernelModule->FindRecord(self, strRecordName);
//        if ( pRecord.get() )
//        {
//            if (pRecord->AddRow(-1, var) >= 0)
//            {
//                return true;
//            }
//        }
//
//        return false;
//    }
//
//    bool AddRecord(const NFIDENTID& self, const std::string& strRecordName, const NFCScriptVarList& TData, const NFCScriptVarList& varKey, const NFCScriptVarList& varDesc, const NFCScriptVarList& varTag, const int nRows, bool bPublic,  bool bPrivate,  bool bSave, bool bView, int nIndex)
//    {
//        return m_pKernelModule->AddRecord(self, strRecordName, TData.GetVar(), varKey.GetVar(), varDesc.GetVar(), varTag.GetVar(), varTag.GetVar(), nRows, bPublic, bPrivate, bSave, bView, nIndex);
//    }
//
//protected:
//
//private:
//    NFIKernelModule* m_pKernelModule;
//    NFIElementInfoModule* m_pElementInfoModule;
//    NFIScriptModule*m_pScriptModule;
//    NFIEventProcessModule* m_pEventProcessModule;
//};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//static  NFIDataList* NFVarList_New()
//{
//    NFIDataList* pVarList = new NFCDataList();
//    return pVarList;
//}
//
//static void NFVarList_Del(NFIDataList* pVarList)
//{
//    if (pVarList)
//    {
//        delete pVarList;
//        pVarList = NULL;
//    }
//}
//
//static void NFVarList_Clear(NFIDataList* pVarList)
//{
//    if (pVarList)
//    {
//        pVarList->Clear();
//    }
//}
//
//static bool NFVarList_IsEmpty(NFIDataList* pVarList)
//{
//    if (pVarList)
//    {
//        pVarList->IsEmpty();
//    }
//
//    return false;
//}
//
//static int NFVarList_GetCount(NFIDataList* pVarList)
//{
//    if (pVarList)
//    {
//        return pVarList->GetCount();
//    }
//
//    return 0;
//}
//
//static TDATA_TYPE NFVarList_Type(NFIDataList* pVarList, const int index)
//{
//    if (pVarList)
//    {
//        return pVarList->Type(index);
//    }
//
//    return TDATA_UNKNOWN;
//}
//
//static bool NFVarList_AddInt(NFIDataList* pVarList, const NFINT64 value)
//{
//    if (pVarList)
//    {
//        return pVarList->Add(value);
//    }
//
//    return false;
//}
//
//static bool NFVarList_AddFloat(NFIDataList* pVarList, const float value)
//{
//    if (pVarList)
//    {
//        return pVarList->Add(value);
//    }
//
//    return false;
//}
//
//static bool NFVarList_AddString(NFIDataList* pVarList, const char* value)
//{
//    if (pVarList)
//    {
//        return pVarList->Add(value);
//    }
//
//    return false;
//}
//
//static bool NFVarList_AddObject(NFIDataList* pVarList, const NFIDENTID& value)
//{
//    if (pVarList)
//    {
//        return pVarList->Add(value);
//    }
//
//    return false;
//}
//
//static bool NFVarList_SetInt(NFIDataList* pVarList, const int index, const NFINT64 value)
//{
//    if (pVarList)
//    {
//        return pVarList->Set(index, value);
//    }
//
//    return false;
//}
//
//static bool NFVarList_SetFloat(NFIDataList* pVarList, const int index, const float value)
//{
//    if (pVarList)
//    {
//        return pVarList->Set(index, value);
//    }
//
//    return false;
//}
//
//static bool NFVarList_SetString(NFIDataList* pVarList, const int index, const char* value)
//{
//    if (pVarList)
//    {
//        return pVarList->Set(index, value);
//    }
//
//    return false;
//}
//
//static bool NFVarList_SetObject(NFIDataList* pVarList, const int index, const NFIDENTID& value)
//{
//    if (pVarList)
//    {
//        return pVarList->Set(index, value);
//    }
//
//    return false;
//}
//
//static NFINT64 NFVarList_IntVal(NFIDataList* pVarList, const int index)
//{
//    if (pVarList)
//    {
//        return pVarList->Int(index);
//    }
//
//    return 0;
//}
//
//static float NFVarList_FloatVal(NFIDataList* pVarList, const int index)
//{
//    if (pVarList)
//    {
//        return pVarList->Float(index);
//    }
//
//    return 0.0f;
//}
//
//static const std::string& NFVarList_StringVal(NFIDataList* pVarList, const int index)
//{
//    if (pVarList)
//    {
//        return pVarList->String(index);
//    }
//
//    return NULL_STR;
//}
//
//static NFIDENTID NFVarList_ObjectVal(NFIDataList* pVarList, const int index)
//{
//    if (pVarList)
//    {
//        return pVarList->Object(index);
//    }
//
//    return NFIDENTID();
//}

//////////////////////////////////////////////////////////////////////////
// static bool KernelModule_RemoveEvent(const NFIKernelModule* pKernelModule, const NFIDENTID& objectID)
// {
//     NFILuaScriptModule* pLuaScriptModule = dynamic_cast<NFILuaScriptModule>(pKernelModule->pPluginManager->FindModule("NFCLuaScriptModule"));
//     pLuaScriptModule->RemoveEvent()objectID;
// 
//     NFCScriptKernelModule* pScriptKernelModule = (NFCScriptKernelModule*)nPtrKernelModule.GetData();
//     if (pScriptKernelModule)
//     {
//         return pScriptKernelModule->RemoveEvent(objectID.GetIdent());
//     }
// 
//     return false;
// }
// 
// static bool KernelModule_RemoveEventCallBack(const NFScriptIdent& nPtrKernelModule,
//                         const NFScriptIdent& objectID, const int nEventID)
// {
//     NFCScriptKernelModule* pScriptKernelModule = (NFCScriptKernelModule*)nPtrKernelModule.GetData();
//     if (pScriptKernelModule)
//     {
//         return pScriptKernelModule->RemoveEventCallBack(objectID.GetIdent(), nEventID);
//     }
// 
//     return false;
// }

static bool KernelModule_DoEvent(NFINT64 kernelAddress, const NFIDENTID& self, const int nEventID, const NFCDataList& valueList)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    NFIEventProcessModule* pEventProcessModule = dynamic_cast<NFIEventProcessModule*>(pKernelModule->GetPluginManager()->FindModule("NFCEventProcessModule"));
    return pEventProcessModule->DoEvent(self, nEventID, valueList);
}

static bool KernelModule_FindHeartBeat(NFIKernelModule* pKernelModule, const NFIDENTID& self, const std::string& strHeartBeatName)
{
    return pKernelModule->FindHeartBeat(self, strHeartBeatName);
}

static bool KernelModule_RemoveHeartBeat(NFIKernelModule* pKernelModule, const NFIDENTID& self, const std::string& strHeartBeatName)
{
    return pKernelModule->RemoveHeartBeat(self, strHeartBeatName);
}

///////////////////////////////////////////////////
static bool KernelModule_ExistElement(NFIKernelModule* pKernelModule, const std::string& strConfigName)
{
    NFIElementInfoModule* pElementInfoModule = dynamic_cast<NFIElementInfoModule*>(pKernelModule->GetPluginManager()->FindModule("NFCElementInfoModule"));
    return pElementInfoModule->ExistElement(strConfigName);
}

static NFINT64 KernelModule_GetElementPropertyInt(NFINT64 kernelAddress, const std::string& strConfigName, const std::string& strPropertyName)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    NFIElementInfoModule* pElementInfoModule = dynamic_cast<NFIElementInfoModule*>(pKernelModule->GetPluginManager()->FindModule("NFCElementInfoModule"));
    return pElementInfoModule->GetPropertyInt(strConfigName, strPropertyName);
}

static float KernelModule_GetElementPropertyFloat(NFINT64 kernelAddress, const std::string& strConfigName, const std::string& strPropertyName)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    NFIElementInfoModule* pElementInfoModule = dynamic_cast<NFIElementInfoModule*>(pKernelModule->GetPluginManager()->FindModule("NFCElementInfoModule"));
    return pElementInfoModule->GetPropertyFloat(strConfigName, strPropertyName);
}

static double KernelModule_GetElementPropertyDouble(NFINT64 kernelAddress, const std::string& strConfigName, const std::string& strPropertyName)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    NFIElementInfoModule* pElementInfoModule = dynamic_cast<NFIElementInfoModule*>(pKernelModule->GetPluginManager()->FindModule("NFCElementInfoModule"));
    return pElementInfoModule->GetPropertyDouble(strConfigName, strPropertyName);
}

static const std::string& KernelModule_GetElementPropertyString(NFIKernelModule* pKernelModule, const std::string& strConfigName, const std::string& strPropertyName)
{
    NFIElementInfoModule* pElementInfoModule = dynamic_cast<NFIElementInfoModule*>(pKernelModule->GetPluginManager()->FindModule("NFCElementInfoModule"));
    return pElementInfoModule->GetPropertyString(strConfigName, strPropertyName);
}

static bool KernelModule_ExistContainer(NFIKernelModule* pKernelModule, const int nContainerIndex)
{
    return pKernelModule->ExistContainer(nContainerIndex);
}

//static bool KernelModule_FindProperty(const NFScriptIdent& nPtrKernelModule, const NFScriptIdent& self, const std::string& strPropertyName)
//{
//    NFCScriptKernelModule* pScriptKernelModule = (NFCScriptKernelModule*)nPtrKernelModule.GetData();
//    if (pScriptKernelModule)
//    {
//        return pScriptKernelModule->FindProperty(self.GetIdent(), strPropertyName);
//    }
//
//    return false;
//}

static bool KernelModule_SetPropertyInt(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName, const int nValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetPropertyInt(self, strPropertyName, nValue);
}

static bool KernelModule_SetPropertyFloat(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName,  const float fValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetPropertyFloat(self, strPropertyName, fValue);
}

static bool KernelModule_SetPropertyDouble(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName,  const double dValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetPropertyDouble(self, strPropertyName, dValue);
}

static bool KernelModule_SetPropertyString(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName, const std::string& strValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetPropertyString(self, strPropertyName, strValue);
}

static bool KernelModule_SetPropertyObject(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName, const NFIDENTID& objectValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetPropertyObject(self, strPropertyName, objectValue);
}

static NFINT64 KernelModule_GetPropertyInt(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetPropertyInt(self, strPropertyName);
}

static float KernelModule_GetPropertyFloat(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetPropertyFloat(self, strPropertyName);
}

static double KernelModule_GetPropertyDouble(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetPropertyDouble(self, strPropertyName);
}

static const std::string& KernelModule_GetPropertyString(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetPropertyString(self, strPropertyName);
}

static NFIDENTID KernelModule_GetPropertyObject(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strPropertyName)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetPropertyObject(self, strPropertyName);
}

static bool KernelModule_SetRecordInt(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol, const int nValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetRecordInt(self, strRecordName, nRow, nCol, nValue);
}

static bool KernelModule_SetRecordFloat(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol,  const float fValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetRecordFloat(self, strRecordName, nRow, nCol, fValue);
}

static bool KernelModule_SetRecordDouble(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol,  const double dValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetRecordDouble(self, strRecordName, nRow, nCol, dValue);
}

static bool KernelModule_SetRecordString(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol, const std::string& strValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetRecordString(self, strRecordName, nRow, nCol, strValue);
}

static bool KernelModule_SetRecordObject(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol, const NFIDENTID& objectValue)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->SetRecordObject(self, strRecordName, nRow, nCol, objectValue);
}

static NFINT64 KernelModule_GetRecordInt(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetRecordInt(self, strRecordName, nRow, nCol);
}

static float KernelModule_GetRecordFloat(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetRecordFloat(self, strRecordName, nRow, nCol);
}

static double KernelModule_GetRecordDouble(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetRecordDouble(self, strRecordName, nRow, nCol);
}

static const std::string& KernelModule_GetRecordString(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetRecordString(self, strRecordName, nRow, nCol);
}

static NFIDENTID KernelModule_GetRecordObject(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    return pKernelModule->GetRecordObject(self, strRecordName, nRow, nCol);
}

static int KernelModule_AddRow(NFINT64 kernelAddress, const NFIDENTID& self, const std::string& strRecordName, const NFCDataList& var)
{
    NFIKernelModule* pKernelModule = (NFIKernelModule*)kernelAddress;
    NF_SHARE_PTR<NFIRecord> pRecord = pKernelModule->FindRecord(self, strRecordName);
    if (nullptr == pRecord)
    {
        return -1;
    }

    return pRecord->AddRow(-1, var);
}

#endif
