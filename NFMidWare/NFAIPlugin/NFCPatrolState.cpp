// -------------------------------------------------------------------------
//    @FileName			:    NFCPatrolState.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2017-02-08
//    @Module           :    NFCPatrolState
//    @Desc             :
// -------------------------------------------------------------------------

#include "NFIStateMachine.h"
#include "NFCPatrolState.h"

NFCPatrolState::NFCPatrolState(float fHeartBeatTime, NFIPluginManager* p)
	: NFIState(PatrolState, fHeartBeatTime, p)
{
	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pAIModule = pPluginManager->FindModule<NFIAIModule>();
	m_pMoveModule = pPluginManager->FindModule<NFIMoveModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pHateModule = pPluginManager->FindModule<NFIHateModule>();
}

bool NFCPatrolState::Enter(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    if (!NFIState::Enter(self, pStateMachine))
    {
        RandomPatrol(self, pStateMachine);
    }

    return true;
}

bool NFCPatrolState::Execute(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    if (!NFIState::Execute(self, pStateMachine))
    {
			NFGUID ident = m_pHateModule->QueryMaxHateObject(self);
			NFAI_MOVE_TYPE eMoveType = (NFAI_MOVE_TYPE)(m_pKernelModule->GetPropertyInt(self, "MoveType"));

			//����Ƕ���ģ����ߣ�����idle
			switch (eMoveType)
			{
			case NFAI_MOVE_TYPE::MOVE_BY_POINT_LIST:
				{
					//�����Ƿ��п��Թ����Ķ���
					if (!ident.IsNull())
					{
						pStateMachine->ChangeState(FightState);
					}
					else
					{
						//��һ���ڵ�
                        //object��¼��ǰ��·��ID��index���Լ�¼Ѱ·��λ��
					}
				}
				break;

			case NFAI_MOVE_TYPE::MOVE_BY_RANDOM:
				{
					//�����Ƿ��п��Թ����Ķ���
					if (!ident.IsNull())
					{
						pStateMachine->ChangeState(FightState);
					}
					else
					{
						RandomPatrol(self, pStateMachine);
					}
				}
				break;
			default:
				break;
			}
    }

    return true;
}

bool NFCPatrolState::Exit(const NFGUID& self, NFIStateMachine* pStateMachine)
{

    return true;
}

bool NFCPatrolState::DoRule(const NFGUID& self, NFIStateMachine* pStateMachine)
{

    return true;
}

bool NFCPatrolState::RandomPatrol(const NFGUID& self, NFIStateMachine* pStateMachine)
{
    //���ȣ��ÿ���û·��

    //û�еĻ�������Ҹ���ַ�߰�(�Գ�����Ϊ���Ŀ�ʼ��,���ӵ�ַ)NPCConfigID
    const std::string& strConfigID = m_pKernelModule->GetPropertyString(self, "NPCConfigID");
    const std::string& strNPCID = m_pKernelModule->GetPropertyString(self, "ConfigID");
    if (!strConfigID.empty())
    {
		NF_SHARE_PTR<NFIPropertyManager> xPropertyManager = m_pElementModule->GetPropertyManager(strConfigID);
		if (xPropertyManager)
		{
			NF_SHARE_PTR<NFIProperty> xPropertyX =  xPropertyManager->GetElement("SeedX");
			NF_SHARE_PTR<NFIProperty> xPropertyY =  xPropertyManager->GetElement("SeedY");
			NF_SHARE_PTR<NFIProperty> xPropertyZ =  xPropertyManager->GetElement("SeedZ");

			float fCurX = xPropertyX->GetFloat();
			float fCurY = xPropertyY->GetFloat();
			float fCurZ = xPropertyZ->GetFloat();

			float fPosOffestX = (float)(rand() / double(RAND_MAX) - 0.5f);
			float fPosOffestZ = (float)(rand() / double(RAND_MAX) - 0.5f);
			fPosOffestX *= 10;
			fPosOffestZ *= 10;

			fCurX += fPosOffestX;
			fCurZ += fPosOffestZ;

			//if (fCurX > 0.0f && fCurZ > 0.0f)
			{
				//���ܷ�Ѱ·������Ѱ·������
				NFAI_STATE eStateType = NFAI_STATE::ChaseState;
				float fRand = (float)(rand() / double(RAND_MAX));
				if (fRand < 0.5f)
				{
					eStateType = NFAI_STATE::ChaseState;
				}

				NFDataList valueList;
				valueList.AddFloat(fCurX);
				valueList.AddFloat(fCurY);
				valueList.AddFloat(fCurZ);
				//m_pKernelModule->DoEvent(self, NFED_ON_CLIENT_REQUIRE_MOVE, valueList);

				m_pKernelModule->SetPropertyFloat(self, "X", fCurX);
				m_pKernelModule->SetPropertyFloat(self, "Y", fCurY);
				m_pKernelModule->SetPropertyFloat(self, "Z", fCurZ);

				return true;
			}
		}
	}

    return false;
}
