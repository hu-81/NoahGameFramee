// -------------------------------------------------------------------------
//    @FileName			:    NFCIdleState.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2017-02-08
//    @Module           :    NFCIdleState
//    @Desc             :
// -------------------------------------------------------------------------

#include "NFIStateMachine.h"
#include "NFCIdleState.h"

NFCIdleState::NFCIdleState(float fHeartBeatTime, NFIPluginManager* p)
	: NFIState(IdleState, fHeartBeatTime, p)
{
    m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
    m_pAIModule = pPluginManager->FindModule<NFIAIModule>();
    m_pMoveModule = pPluginManager->FindModule<NFIMoveModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pHateModule = pPluginManager->FindModule<NFIHateModule>();
}

NFCIdleState::~NFCIdleState()
{

}

bool NFCIdleState::Enter(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    if (!NFIState::Enter(self, pStateMachine))
    {

			//���Ƿ���ս������
            switch (pStateMachine->LastState())
            {
                case NFAI_STATE::FightState:
                    //���˼�����
                    Execute(self, pStateMachine);
                    break;

                default:
                    break;
            }
    }

    return true;
}

bool NFCIdleState::Execute(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    if (!NFIState::Execute(self, pStateMachine))
    {

            //�����Ƿ��п��Թ����Ķ���
            NFGUID ident = m_pHateModule->QueryMaxHateObject(self);
            if (!ident.IsNull())
            {
                pStateMachine->ChangeState(FightState);
            }
            else
            {
                if (m_pKernelModule->GetPropertyInt(self, "MoveSpeed") > 0)
                {
                    RandomIdle(self, pStateMachine);
                }
            }
    }

    return true;
}

bool NFCIdleState::Exit(const NFGUID& self, NFIStateMachine* pStateMachine)
{


    return true;
}

bool NFCIdleState::DoRule(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    return true;
}

bool NFCIdleState::RandomIdle(const NFGUID& self, NFIStateMachine* pStateMachine)
{
	//����Ƕ���ģ����ߣ�����idle
	NFAI_MOVE_TYPE eMoveType = (NFAI_MOVE_TYPE)(m_pKernelModule->GetPropertyInt(self, "MoveType"));

	switch (eMoveType)
	{
	case NFAI_MOVE_TYPE::MOVE_BY_POINT_LIST:
	case NFAI_MOVE_TYPE::MOVE_BY_RANDOM:
		{
			float fRand = (float)(rand() / double(RAND_MAX));
			if (fRand < 0.4f)
			{
				pStateMachine->ChangeState(PatrolState);
			}
		}
		break;

	default:
		break;
	}

    return false;
}
