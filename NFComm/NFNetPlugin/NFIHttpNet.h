
#ifndef NFI_HTTP_NET_H
#define NFI_HTTP_NET_H

#include <cstring>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include <list>
#include <vector>
#include <assert.h>

#if NF_PLATFORM == NF_PLATFORM_WIN
#include <WinSock2.h>
#include <windows.h>
#else
#include <unistd.h>
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

enum NFWebStatus
{
	WEB_OK = 200,
	WEB_ERROR = 404,
	EB_TIMEOUT = 503,
};

class NFHttpRequest
{
public:
	void* req;
	int nCommand;
	std::string url;
};

class NFHttpHeader
{

};

class NFHttpBody
{

};
//it should be
//typedef std::function<void(const NFHttpRequest& req, const int nCommand, const std::string& strData, const std::string& strUrl)> HTTP_RECEIVE_FUNCTOR;
typedef std::function<void(const NFHttpRequest& req, const std::string& strCommand, const std::string& strUrl)> HTTP_RECEIVE_FUNCTOR;
typedef std::shared_ptr<HTTP_RECEIVE_FUNCTOR> HTTP_RECEIVE_FUNCTOR_PTR;

class NFIHttpNet
{
public:
	virtual bool Execute() = 0;
	virtual int InitServer(const unsigned short nPort) = 0;
	virtual bool Final() = 0;

public:
	//
	//virtual bool PostMsg(const std::string& strUrl, const NFHttpHeader& xHeader, const NFHttpBody& xBody) = 0;

	virtual bool ResponseMsg(const NFHttpRequest & req, const std::string& strMsg, NFWebStatus code, const std::string& strReason = "OK") = 0;
	virtual bool ResponseFile(const NFHttpRequest& req, const std::string& strPath, const std::string& strFileName) = 0;
};

#endif
