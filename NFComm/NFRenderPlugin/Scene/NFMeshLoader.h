/*
            This file is part of:
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2020 NoahFrame(NoahGameFrame)

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

#ifndef NF_MESH_LOADER
#define NF_MESH_LOADER

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/fwd.hpp"
#include "NFMeshComponent.h"
#include "NFComm/NFCore/NFVector3.hpp"
#include "NFComm/NFPluginModule/NFPlatform.h"


class NFMeshLoader
{
public:
    NF_SHARE_PTR<NFSceneNode> LoadMesh(const std::string& path);
    void SaveMesh(const NF_SHARE_PTR<NFSceneNode> mesh, const std::string& path);

    bool LoadOBJ(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals);
    bool LoadAssImp(const char* path, std::vector<unsigned short>& indices, std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals);

};

#endif // !NF_MESH_LOADER