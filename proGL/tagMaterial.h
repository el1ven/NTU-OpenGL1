//
//  tagMaterial.h
//  proGL
//
//  Created by el1ven on 2/9/14.
//  Copyright (c) 2014 el1ven. All rights reserved.
//

#ifndef __proGL__tagMaterial__
#define __proGL__tagMaterial__

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"

using namespace std;

class tagMaterial{
public:
    int groupId = 0;//保存组的id值
    string mtlName = "";//每个部分的材质名称
    vector<Vector3> mtlKa;//环境光反射
    vector<Vector3> mtlKd;//漫反射
    vector<Vector3> mtlKs;//镜面反射
    int mtlIllum = 0;// 材质光照模型
    float mtlD = 1.0;//渐隐指数,表示物体融入环境的数量
    float mtlNs = 0.0;//反射指数
    bool hasKa = false;
    bool hasKd = false;
    bool hasKs = false;
    bool hasIllum = false;
    bool hasD = false;
    bool hasNs = false;
};


#endif /* defined(__proGL__tagMaterial__) */
