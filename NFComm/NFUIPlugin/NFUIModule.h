/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2019 NoahFrame(NoahGameFrame)

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

#ifndef NF_UI_MODULE_H
#define NF_UI_MODULE_H

#include "NFComm/NFPluginModule/NFILogModule.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIClassModule.h"
#include "NFComm/NFPluginModule/NFIUIModule.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "glad/glad.h"
#include <stdio.h>
#include <SDL.h>

/*


class NFSceneView : public NFIView
{
public:
    NFSceneView(NFViewType vt)
    :NFIView(vt)
    {
        
    }
};

class NFHierachyView : public NFIView
{
public:
    NFHierachyView(NFViewType vt)
    :NFIView(vt)
    {
        
    }
};

class NFConsoleView : public NFIView
{
public:
    NFConsoleView(NFViewType vt)
    :NFIView(vt)
    {
        
    }
};

class NFProfileView : public NFIView
{
public:
    NFProfileView(NFViewType vt)
    :NFIView(vt)
    {
        
    }
};

class NFInspectorView : public NFIView
{
public:
    NFInspectorView(NFViewType vt)
    :NFIView(vt)
    {
        
    }

private:
    NFIView* mPropsView;
    NFIView* mRecordsView;
};

class NFBluePrintView : public NFIView
{
public:
    NFBluePrintView(NFViewType vt)
    :NFIView(vt)
    {
        
    }
};

class NFProjectView : public NFIView
{
public:
    NFProjectView(NFViewType vt)
    :NFIView(vt)
    {
        
    }

    private:
        NFIView* mFolderView;
        NFIView* mFilesView;
};

class NFGameView : public NFIView
{
public:
    NFGameView(NFViewType vt)
    :NFIView(vt)
    {
        
    }
};

*/
class NFUIModule
    : public NFIUIModule
{
public:
    NFUIModule( NFIPluginManager* p )
    {
        pPluginManager = p;
    }

    virtual ~NFUIModule() {};

    virtual bool Awake();
    virtual bool Init();
    virtual bool AfterInit();
    virtual bool CheckConfig();
    virtual bool ReadyExecute();
    virtual bool Execute();
    virtual bool BeforeShut();
    virtual bool Shut();
    virtual bool Finalize();
    virtual bool OnReloadPlugin();

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	SDL_Window* window;
	bool done = false;
	SDL_GLContext gl_context;

private:
    std::list<NF_SHARE_PTR<NFIView>> mViewList;
};




#endif
