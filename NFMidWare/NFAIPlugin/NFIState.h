// -------------------------------------------------------------------------
//    @FileName			:    NFIState.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2017-02-08
//    @Module           :    NFIState
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef NFI_STATE_H
#define NFI_STATE_H

#include "NFComm/NFCore/NFDataList.hpp"
#include "NFComm/NFPluginModule/NFIPluginManager.h"

//���е�״̬
enum NFAI_MOVE_TYPE
{
	NO_MOVE_TYPE,              // ���ߵģ�����
	MOVE_BY_POINT_LIST,        // ·��Ѳ��
	MOVE_BY_RANDOM,            // ���Ѳ��
	MOVE_BY_PLAYER_AI,         // Player's ai
};

//���е�״̬
enum NFAI_STATE
{
    State_Error = 0,
    IdleState,                  // ����״̬
    PatrolState,                // Ѳ��״̬
    FightState,                 // ս��״̬
    ChaseState,                 // ׷��״̬
    DeadState,                  // ����״̬
};

class NFIStateMachine;

class NFIState
	: public NFIModule
{
public:
    NFIState(NFAI_STATE eState, const float fHeartBeatTime, NFIPluginManager* p)
    {
        meState = eState;
        mfHeartBeatTime = fHeartBeatTime;
        pPluginManager = p;
    }

    virtual ~NFIState()
    {
    }

    virtual bool DoRule(const NFGUID& self, NFIStateMachine* pStateMachine)
    {
        //����true��ʾ���ദ���������ͱ�����
        return false;
    }

    virtual bool Enter(const NFGUID& self, NFIStateMachine* pStateMachine)
    {
        return false;
    }

    virtual bool Execute(const NFGUID& self, NFIStateMachine* pStateMachine)
    {
        return false;
    }

    virtual bool Exit(const NFGUID& self, NFIStateMachine* pStateMachine)
    {
        return false;
    }

    const NFAI_STATE GetCurrState()
    {
        return meState;
    }

    float GetHeartBeatTime()
    {
        return mfHeartBeatTime;
    }

protected:
    NFAI_STATE  meState;
    float               mfHeartBeatTime;
};

#endif