#ifndef NFC_REDIS_MGR_H
#define NFC_REDIS_MGR_H



#include "NFRedisImpl.h"


static const int MAX_REIDS_CONNECT_COUNT = 100;

using RedisImplPtr = std::shared_ptr<NFCRedisImpl>;

class NFCRedisMgr 
{
public:
	NFCRedisMgr();
	~NFCRedisMgr();

	static NFCRedisMgr& getInstance();

	// ���һ��redis���ӵ�ʵ��
	RedisImplPtr GetImpl();

	// ���߳��д�������
	int Init(const char* pIp, unsigned short port);

	// ɾ���̴߳�������
	int DeleteRedisInThread();
	
	int Final();

private:

	std::map<std::thread::id, RedisImplPtr> _mapConnect;

	std::string _szIP;
	unsigned short _port;
};


#endif

