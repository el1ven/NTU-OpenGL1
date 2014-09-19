//
//  oneFace.h
//  proGL
//
//  Created by el1ven on 3/9/14.
//  Copyright (c) 2014 el1ven. All rights reserved.
//

#ifndef __proGL__oneFace__
#define __proGL__oneFace__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class oneFace{
public:
    int groupId;//属于哪个组
    vector<string> oneFaceData;
    vector<int> oneFaceVertexIndex;
    vector<int> oneFaceTextureIndex;
    vector<int> oneFaceNormalIndex;
    
};

#endif /* defined(__proGL__oneFace__) */
