#include "HelloWorld3Module.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"
#include "NFComm/NFPluginModule/NFIEventModule.h"

bool HelloWorld3Module::Init()
{
	//��ʼ��
	std::cout << "Hello, world3, Init" << std::endl;

	return true;
}

int HelloWorld3Module::OnEvent(const NFGUID& self, const NFEventDefine event, const NFIDataList& arg)
{
	//�¼��ص�����
	std::cout << "OnEvent EventID: " << event << " self: " << self.nData64 << " argList: " << arg.Int(0) << " " << " " << arg.String(1) << std::endl;

	m_pKernelModule->SetPropertyInt(self, "Hello", arg.Int(0));
	m_pKernelModule->SetPropertyString(self, "Hello", arg.String(1));

	return 0;
}

int HelloWorld3Module::OnHeartBeat(const NFGUID& self, const std::string& strHeartBeat, const float fTime, const int nCount)
{

	unsigned long unNowTime = m_pKernelModule->GetTime();

	std::cout << "strHeartBeat: " << fTime << " Count: " << nCount << "  TimeDis: " << unNowTime - mLastTime << std::endl;

	mLastTime = unNowTime;

	return 0;
}

int HelloWorld3Module::OnClassCallBackEvent(const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT event, const NFIDataList& arg)
{
	//�������¼���ֻҪ�д������ഴ���������ټ���ص�
	std::cout << "OnClassCallBackEvent ClassName: " << strClassName << " ID: " << self.nData64 << " Event: " << event << std::endl;

	if (event == COE_CREATE_HASDATA)
	{
		m_pEventModule->AddEventCallBack(self, NFEventDefine(1), this, &HelloWorld3Module::OnEvent);

		m_pScheduleModule->AddSchedule(self, "OnHeartBeat", this, &HelloWorld3Module::OnHeartBeat, 5.0f, 10 );

		mLastTime = m_pKernelModule->GetTime();
	}

	return 0;
}

int HelloWorld3Module::OnPropertyCallBackEvent( const NFGUID& self, const std::string& strProperty, const NFIDataList::TData& oldVar, const NFIDataList::TData& newVar)
{
	//���Իص��¼���ֻҪ����ֵ�����б仯���ͻᱻ�ص�
	std::cout << "OnPropertyCallBackEvent Property: " << strProperty << " OldValue: " << oldVar.GetInt() << " NewValue: " << newVar.GetInt() << std::endl;

	return 0;
}

int HelloWorld3Module::OnPropertyStrCallBackEvent( const NFGUID& self, const std::string& strProperty, const NFIDataList::TData& oldVar, const NFIDataList::TData& newVar)
{
	//���Իص��¼���ֻҪ����ֵ�����б仯���ͻᱻ�ص�
	std::cout << "OnPropertyCallBackEvent Property: " << strProperty << " OldValue: " << oldVar.GetString() << " NewValue: " << newVar.GetString() << std::endl;

	return 0;
}

bool HelloWorld3Module::AfterInit()
{
	//��ʼ�����
	std::cout << "Hello, world3, AfterInit" << std::endl;

	m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
	m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
	m_pEventModule = pPluginManager->FindModule<NFIEventModule>();
	m_pScheduleModule = pPluginManager->FindModule<NFIScheduleModule>();
	
	//�������������еĶ��������������
	m_pKernelModule->CreateScene(1);

	m_pKernelModule->AddClassCallBack(NFrame::Player::ThisName(), this, &HelloWorld3Module::OnClassCallBackEvent);

	//�������󣬹���ص������Իص�,Ȼ���¼��������
	NF_SHARE_PTR<NFIObject> pObject = m_pKernelModule->CreateObject(NFGUID(0, 10), 1, 0, NFrame::Player::ThisName(), "", NFCDataList());
	if (!pObject.get())
	{
		return false;
	}

	pObject->GetPropertyManager()->AddProperty(pObject->Self(), "Hello", TDATA_STRING);
	pObject->GetPropertyManager()->AddProperty(pObject->Self(), "World", TDATA_INT);

	pObject->AddPropertyCallBack("Hello", this, &HelloWorld3Module::OnPropertyStrCallBackEvent);
	pObject->AddPropertyCallBack("World", this, &HelloWorld3Module::OnPropertyCallBackEvent);

	pObject->SetPropertyString("Hello", "hello,World");
	pObject->SetPropertyInt("World", 1111);


	m_pEventModule->DoEvent(pObject->Self(), NFEventDefine(1), NFCDataList() << int(100) << "200");

	return true;
}

bool HelloWorld3Module::Execute()
{
	//ÿִ֡��
	//std::cout << "Hello, world3, Execute" << std::endl;

	return true;
}

bool HelloWorld3Module::BeforeShut()
{
	//����ʼ��֮ǰ
	std::cout << "Hello, world3, BeforeShut" << std::endl;

	m_pKernelModule->DestroyAll();

	return true;
}

bool HelloWorld3Module::Shut()
{
	//����ʼ��
	std::cout << "Hello, world3, Shut" << std::endl;

	return true;
}
