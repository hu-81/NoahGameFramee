/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2018 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef NFI_THREAD_POOL_MODULE_H
#define NFI_THREAD_POOL_MODULE_H

#include "NFIModule.h"
#include <thread>

///////////////////////////////////////////////////

typedef std::function<int(const int, const int, std::string&)> TASK_PROCESS_FUNCTOR;
typedef NF_SHARE_PTR<TASK_PROCESS_FUNCTOR> TASK_PROCESS_FUNCTOR_PTR;


class NFThreadTask
{
	int nTaskID;
	int nFormThread;
	std::string data;
	TASK_PROCESS_FUNCTOR_PTR xThreadFuncptr;
	TASK_PROCESS_FUNCTOR_PTR xEndFuncptr;
};

class NFThreadCell
{
public:

	NFThreadCell()
	{
		mThread = NF_SHARE_PTR<std::thread>(NF_NEW std::thread(Execute));
	}

protected:
	static void Execute()
	{

	}
private:
	std::list<NFThreadTask> mTaskList;
	NF_SHARE_PTR<std::thread> mThread;
};

class NFIThreadPoolModule : public NFIModule
{
public:
	int DoTask(const std::string& data, TASK_PROCESS_FUNCTOR asyncFunctor, TASK_PROCESS_FUNCTOR functor_end)
	{
		return DoTask(0, data, asyncFunctor, functor_end);
	}

	int DoTask(const int hash, const std::string& data,
		TASK_PROCESS_FUNCTOR asyncFunctor, TASK_PROCESS_FUNCTOR functor_end)
	{
		return 1;
	}

	int DoTask(const NFGUID taskID, const std::string& data,
		TASK_PROCESS_FUNCTOR asyncFunctor, TASK_PROCESS_FUNCTOR functor_end)
	{
		return DoTask(0, taskID, data,  asyncFunctor, functor_end);
	}

	int DoTask(const int hash, const NFGUID taskID, const std::string& data,
		TASK_PROCESS_FUNCTOR asyncFunctor, TASK_PROCESS_FUNCTOR functor_end)
	{
		return 1;
	}
};

#endif
