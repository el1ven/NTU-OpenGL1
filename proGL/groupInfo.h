//
//  groupInfo.h
//  proGL
//
//  Created by el1ven on 3/9/14.
//  Copyright (c) 2014 el1ven. All rights reserved.
//

#ifndef __proGL__groupInfo__
#define __proGL__groupInfo__

#include "tagMaterial.h"
#include "Vector3.h"
#include "oneFace.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class groupInfo{
public:
    bool hasTexture = false;//是否具有纹理坐标
    bool hasNormal = false;//是否具有法线向量
    bool hasMat = false;//此组是否具有材质
    string groupName;//组的名称
    //tagMaterial tMat;//引入材质对象
    vector<oneFace> groupFace;//存储一个组有多少个面
    vector<tagMaterial> groupMat;
    //vector<Vector3> groupVertexs;//本组的顶点索引信息
    //vector<Vector3> groupTextures;//本组的纹理信息
    //vector<Vector3> groupNormals;//本组的发线信息
};

#endif /* defined(__proGL__groupInfo__) */
