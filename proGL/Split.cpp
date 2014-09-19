//
//  Split.cpp
//  proGL
//
//  Created by el1ven on 31/8/14.
//  Copyright (c) 2014 el1ven. All rights reserved.
//

#include "Split.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> Split::splitMethod(string str, string pattern){
    
    int pos;
    vector<string> result;
    
    str+=pattern;//便于处理，所以把它们相加
    int size = (int)(str.size());
    
    for(int i = 0; i < size; i++){
        pos = (int)(str.find(pattern, i));
        if(pos < size){
            string s = str.substr(i, pos-i);
            result.push_back(s);
            i = (int)(pos + pattern.size() - 1);
        }
    }
    
    return result;
}