//
//  tag3DModel.h
//  proGL
//
//  Created by el1ven on 29/8/14.
//  Copyright (c) 2014 el1ven. All rights reserved.
//

#ifndef __proGL__tag3DModel__
#define __proGL__tag3DModel__

#include <iostream>
#include <vector>
#include "groupInfo.h"
#include "tagMaterial.h"
#include "Vector3.h"

using namespace std;

class tag3DModel{//模型信息
public:
    bool hasTextures = false;
    bool hasNormals = false;
    //int numOfGroupWithMat;//有材质的组的个数
    void parse(const char* fileName);//解析文件
    void draw();//画出图形
    void parseMtl(const char *fileName);//解析材质文件
    void addTransf(float angle, float x, float y, float z);//增加transform函数
    vector<groupInfo> groupSet;//引入组对象，包含一个组的所有信息
    vector<tagMaterial> matSet;//包含所有组的材质组名和名称
    vector<Vector3> nTexturesPoint;
    vector<Vector3> nNormalsPoint;
    vector<Vector3> nVertexsPoint;
    vector<tagMaterial> nMaterialPoint;//存储读取的材质信息库
    //vector<tagMaterial> nMaterialPoint2;
};

#endif /* defined(__proGL__tag3DModel__) */
