//
//  tag3DModel.cpp
//  proGL
//
//  Created by el1ven on 29/8/14.
//  Copyright (c) 2014 el1ven. All rights reserved.
//

#include "tag3DModel.h"
#include "tagMaterial.h"
#include "groupInfo.h"
#include <GLUT/GLUT.h>
#include "Vector3.h"
#include "Split.h"
#include "oneFace.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <String>
#include <string>



int ii = 0;//记录组的个数并给组的id提供信息

int jj = 0;//存储材质的时候需要分组存储

int kk = 0;//处理材质文件的分组

int numOfVn = 0;//测试法线的数目

int numOfGroupWithMat = 0;//记录有材质组的个数

//vector<int> countGrpForMat;//记录材质的组数

//string label = "abc";

void tag3DModel::parse(const char *fileName){//解析文件
    
    //cout<<"Enter the parse function"<<endl;
    
    string *str = new string() ;//每行开头无用的字母
    ifstream fin(fileName);
    string *everyLine = new string();//每一行数据

    if(!fin){
        cout<<"Fail to open file!"<<endl;
        return;
    }
    
    while(getline(fin,*everyLine)){//开始读取文件
        
        if((*everyLine)[0] == 'v'){
            if((*everyLine)[1] == 't'){//vt纹理坐标
         
                cout<<"Enter the vt"<<endl;
         
                hasTextures = true;//证明有纹理坐标
                
                istringstream sin1(*everyLine);
                string *s1 = new string();
                string *s2 = new string();
                string *s3 = new string();
                sin1>>*str>>*s1>>*s2>>*s3;
                
                Vector3 *v = new Vector3();
                
                istringstream *stream1 = new istringstream();
                (*stream1).str(*s1);
                float *index1 = new float();
                (*stream1) >> *index1;
                (*v).x = *index1;
                delete stream1;
                delete index1;
                
                istringstream *stream2 = new istringstream();
                (*stream2).str(*s2);
                float *index2 = new float();
                (*stream2) >> *index2;
                (*v).y = *index2;
                delete stream2;
                delete index2;
                
                istringstream *stream3 = new istringstream();
                (*stream3).str(*s3);
                float *index3 = new float();
                (*stream3) >> *index3;
                (*v).z = *index3;
                delete stream3;
                delete index3;
                
                nTexturesPoint.push_back(*v);
                sin1.clear();
                delete v;
                
            }else if((*everyLine)[1] == 'n'){//vn法线
                
                //cout<<"Enter the vn"<<endl;
                
                hasNormals = true;//证明有法线向量
                
                istringstream sin2((*everyLine));
                string *s1 = new string();
                string *s2 = new string();
                string *s3 = new string();
                
                sin2>>*str>>*s1>>*s2>>*s3;
                
                
                Vector3 *v = new Vector3();
                
                istringstream *stream1 = new istringstream();
                (*stream1).str(*s1);
                float *index1 = new float();
                (*stream1) >> *index1;
 
                (*v).x = *index1;
                //cout<<(*v).x<<endl;
                
                delete stream1;
                delete index1;
                delete s1;
                
                istringstream *stream2 = new istringstream();
                (*stream2).str(*s2);
                float *index2 = new float();
                (*stream2) >> *index2;
                
                (*v).y = *index2;
                //cout<<(*v).y<<endl;
                
                delete stream2;
                delete index2;
                delete s2;

                istringstream *stream3 = new istringstream();
                (*stream3).str(*s3);
                double *index3 = new double();
                (*stream3) >> *index3;
                
                (*v).z = *index3;
                //cout<<(*v).z<<endl;
                
                delete stream3;
                delete index3;
                delete s3;

                //cout<<(*v).x<<"*"<<(*v).y<<"*"<<(*v).z<<endl;
                
                nNormalsPoint.push_back(*v);
                
                sin2.clear();
                
                //numOfVn++;
                //cout<<numOfVn<<endl;
                
                if(v != nullptr){
                    //cout<<"v of vn is not empty"<<endl;
                    delete v;
                }
            
            }else{//单纯的v顶点
                
                istringstream sin3(*everyLine);
                string s1,s2,s3 = "";
                sin3>>*str>>s1>>s2>>s3;
                
                Vector3 *v = new Vector3();
                
                istringstream stream1;
                stream1.str(s1);
                float index1;
                stream1 >> index1;
                (*v).x = index1;
                stream1.clear();
                
                istringstream stream2;
                stream2.str(s2);
                float index2;
                stream2 >> index2;
                (*v).y = index2;
                stream2.clear();
                
                istringstream stream3;
                stream3.str(s3);
                float index3;
                stream3 >> index3;
                (*v).z = index3;
                stream3.clear();
                
                //cout<<(*v).x<<" "<<(*v).y<<" "<<(*v).z<<endl;
                
                nVertexsPoint.push_back(*v);
                sin3.clear();
                
                if(v != nullptr){
                    //cout<<"v of v is not empty"<<endl;
                    delete v;
                }
            }
            
        }
        
        if( (*everyLine)[0] == 'g' && (*everyLine)[1] != 'r' && (*everyLine).length() > 1)//去掉第一个无用的g, &&条件是有先后顺序的！！！
        {
            //cout<<"Enter the group"<<endl;
            
            istringstream sin((*everyLine));
            string *s1 = new string();
            sin>>*str>>*s1;
            //cout<<*s1<<endl;
            
            groupInfo *grp = new groupInfo();
            (*grp).groupName = *s1;
            groupSet.push_back(*grp);
            
            //label = *s1;
            
            sin.clear();
            delete s1;
            delete grp;
            
            ii++;
            //cout<<ii<<endl;
            //cout<<"delete the group!"<<endl;
        }


        if((*everyLine)[0] == 'f'){

            //cout<<"Enter the face function"<<endl;
            oneFace *face = new oneFace();
            (*face).groupId = ii-1;//记录此行face属于哪个组
            //cout<<(*face).groupId<<endl;
        
            Split *sp1  = new Split();
            vector<string> *temp1 = new vector<string>();//存的一行face数据，没有去掉前导空格
            *temp1 = sp1->splitMethod((*everyLine), " ");
            vector<string>::iterator it1;
            it1 = (*temp1).begin();
            it1++;
            
            for(; it1 != (*temp1).end(); it1++){
                (*face).oneFaceData.push_back(*it1);
                //cout<<*it1<<endl;
            }
            
            delete temp1;
            
            for(int i = 0; i < (*face).oneFaceData.size(); i++){
                
                string s1 = "";
                s1 = (*face).oneFaceData[i];
                if(s1.find("/") != string::npos){//如果这个面有／，也就是有vt,vn
                    Split *sp2 = new Split();
                    vector<string> *temp2  = new vector<string>();
                    *temp2 = sp2->splitMethod(s1, "/");
                    delete sp2;
                    
                    //cout<<s1<<"有vt,vn有斜杠，需要继续分割"<<endl;
                  
                    if((*temp2)[0].length() > 0 ){//v
                        
                        //(*face).oneFaceVertexIndex.clear();
                        
                        //cout<<(*temp2)[0]<<endl;
                        string *s = new string();
                        *s = (*temp2)[0];
                        int *index = new int();
                        istringstream stream1(*s);
                        stream1>>*index;
                        //cout<<*index<<endl;
                        
                        (*face).oneFaceVertexIndex.push_back(*index);
                        
                        delete s;
                        delete index;
                        stream1.clear();
                    }
                    
                    if((*temp2)[1].length() > 0 ){//vt
                        
                        //(*face).oneFaceTextureIndex.clear();
                        
                        //cout<<(*temp2)[1]<<endl;
                        string *s = new string();
                        *s = (*temp2)[1];
                        int *index = new int();
                        istringstream stream1(*s);
                        stream1>>*index;
                        //cout<<*index<<endl;
                        
                        (*face).oneFaceTextureIndex.push_back(*index);
                        
                        delete s;
                        delete index;
                        stream1.clear();
                    }
                    
                    if((*temp2)[2].length() > 0 ){//vn
                        
                        //(*face).oneFaceNormalIndex.clear();
                        
                        //cout<<(*temp2)[2]<<endl;
                        string *s = new string();
                        *s = (*temp2)[2];
                        int *index = new int();
                        istringstream stream1(*s);
                        stream1>>*index;
                        //cout<<*index<<endl;
                        (*face).oneFaceNormalIndex.push_back(*index);
                        
                        delete s;
                        delete index;
                        stream1.clear();
                    }
                    
                }else{//只有一个参数v
                    
                    //(*face).oneFaceVertexIndex.clear();
                    
                    int *index = new int();
                    istringstream stream1(s1);
                    stream1>>*index;
                    //cout<<*index<<endl;
                    
                    (*face).oneFaceVertexIndex.push_back(*index);
                    
                    delete index;
                    stream1.clear();
                }
            }
            
            //组是从零开始编号的
            groupSet[ii-1].groupFace.push_back(*face);//把属于本组的面存入相应的组里
            //cout<<ii-1<<endl;
            delete face;
            
        }

        
        if((*everyLine)[0] == 'u' && (*everyLine)[1] == 's'){//读取组的材质信息
            
            //cout<<"有材质的组的ID"<<ii-1<<"*";
            
            istringstream sin((*everyLine));
            string *s1 = new string();
            sin>>*str>>*s1;
            
            //cout<<"有材质的组所用的材质名称"<<*s1<<endl;
            
            tagMaterial *tMat = new tagMaterial();//新建一个材质对象
            (*tMat).groupId = ii - 1;
            (*tMat).mtlName = *s1;
            
            //matSet.push_back(*tMat);//存到信息组中
            groupSet[ii-1].groupMat.push_back(*tMat);
            groupSet[ii-1].groupName = *s1;
            groupSet[ii-1].hasMat = true;
            
            delete s1;
            delete tMat;
            
            //jj++;
            //numOfGroupWithMat = jj;
            //cout<<"有材质的组的个数:"<<numOfGroupWithMat<<endl;
            
            
            
            /*//cout<<"Enter the usemtl"<<endl;
            tagMaterial *tMat = new tagMaterial();//新建一个材质对象
            
            //cout<<"*"<<jj<<endl;
            (*tMat).groupId  = jj;//记录组号,这里的0对应groupSet第一个对象的位置，也就知道材质名称
            //cout<<(*tMat).groupId<<endl;
            
            istringstream sin((*everyLine));
            string *s1 = new string();
            sin>>*str>>*s1;
            (*tMat).mtlName = *s1;//存储材质名字信息
            matSet.push_back(*tMat);
            
            sin.clear();
            delete tMat;
            delete s1;
            
            jj++;
            numOfGroupWithMat = jj;
            //cout<<numOfGroupWithMat<<endl;
            //cout<<jj<<endl;
            //cout<<"delete the tMat object!"<<endl;*/
        }
        
    }
    fin.close();
    delete everyLine;
    delete str;
}


void tag3DModel::parseMtl(const char *fileName2){//解析材质文件
    string *str = new string();//每行开头无用的字母
    ifstream fin2(fileName2);
    string *everyLine = new string();//每一行数据
    
    if(!fin2){
        cout<<"Fail to open the mtl file!"<<endl;
        return;
    }
    
    //nMaterialPoint.clear();
    
    while(getline(fin2,*everyLine)){//开始读文件
        
        if((*everyLine)[0] == 'n'){//存储材质名称
            istringstream sin2((*everyLine));
            string *s = new string();
            sin2>>*str>>*s;
            //cout<<*s<<endl;
            tagMaterial *tMat = new tagMaterial();//新建材质对象
            (*tMat).mtlName = *s;
            //cout<<(*tMat).mtlName<<endl;
            //nMaterialPoint.reserve(100);
            nMaterialPoint.push_back(*tMat);
            //cout<<kk<<endl;
            kk++;//记录组数
            sin2.clear();
            delete s;
            delete tMat;
        }
        
        if((*everyLine)[0] == 'K' && (*everyLine)[1] == 'a'){//Ka
            istringstream sin(*everyLine);
            string *s1 = new string();
            string *s2 = new string();
            string *s3 = new string();
            sin>>*str>>*s1>>*s2>>*s3;
            //cout<<*s1<<":"<<*s2<<":"<<*s3<<endl;
            
            Vector3 *v1 = new Vector3();
            
            istringstream *stream1 = new istringstream();
            (*stream1).str(*s1);
            float *index1 = new float();
            (*stream1) >> *index1;
            (*v1).x = *index1;
            //cout<<(*v1).x<<endl;
            delete stream1;
            delete index1;
            delete s1;
            
            istringstream *stream2 = new istringstream();
            //cout<<*s2<<endl;
            (*stream2).str(*s2);
            float *index2 = new float();
            (*stream2) >> *index2;
            //cout<<*index2<<endl;
            (*v1).y = *index2;
            //cout<<(*v1).y<<endl;
            delete stream2;
            delete index2;
            delete s2;
            
            istringstream *stream3 = new istringstream();
            (*stream3).str(*s3);
            float *index3 = new float();
            (*stream3) >> *index3;
            (*v1).z = *index3;
            delete stream3;
            delete index3;
            delete s3;
            
            //cout<<(*v1).x<<" "<<(*v1).y<<" "<<(*v1).z<<endl;
            
            //int id = kk;
            //cout<<kk-1<<endl;
            nMaterialPoint[kk-1].mtlKa.push_back(*v1);
            sin.clear();
            delete v1;
        }
        
        if((*everyLine)[0] == 'K' && (*everyLine)[1] == 'd'){//Kd
            istringstream sin(*everyLine);
            string *s1 = new string();
            string *s2 = new string();
            string *s3 = new string();
            sin>>*str>>*s1>>*s2>>*s3;
            //cout<<*s1<<":"<<*s2<<":"<<*s3<<endl;
            
            Vector3 *v1 = new Vector3();
            
            istringstream *stream1 = new istringstream();
            (*stream1).str(*s1);
            float *index1 = new float();
            (*stream1) >> *index1;
            (*v1).x = *index1;
            //cout<<(*v1).x<<endl;
            delete stream1;
            delete index1;
            delete s1;
            
            istringstream *stream2 = new istringstream();
            //cout<<*s2<<endl;
            (*stream2).str(*s2);
            float *index2 = new float();
            (*stream2) >> *index2;
            //cout<<*index2<<endl;
            (*v1).y = *index2;
            //cout<<(*v1).y<<endl;
            delete stream2;
            delete index2;
            delete s2;
            
            istringstream *stream3 = new istringstream();
            (*stream3).str(*s3);
            float *index3 = new float();
            (*stream3) >> *index3;
            (*v1).z = *index3;
            delete stream3;
            delete index3;
            delete s3;
            
            //cout<<(*v1).x<<" "<<(*v1).y<<" "<<(*v1).z<<endl;
            
            //int id = kk;
            //cout<<"*"<<kk-1<<endl;
            nMaterialPoint[kk-1].mtlKd.push_back(*v1);
            sin.clear();
            delete v1;
        }
        
        if((*everyLine)[0] == 'K' && (*everyLine)[1] == 's'){//Ks
            istringstream sin(*everyLine);
            string *s1 = new string();
            string *s2 = new string();
            string *s3 = new string();
            sin>>*str>>*s1>>*s2>>*s3;
            //cout<<*s1<<":"<<*s2<<":"<<*s3<<endl;
            
            Vector3 *v1 = new Vector3();
            
            istringstream *stream1 = new istringstream();
            (*stream1).str(*s1);
            float *index1 = new float();
            (*stream1) >> *index1;
            (*v1).x = *index1;
            //cout<<(*v1).x<<endl;
            delete stream1;
            delete index1;
            delete s1;
            
            istringstream *stream2 = new istringstream();
            //cout<<*s2<<endl;
            (*stream2).str(*s2);
            float *index2 = new float();
            (*stream2) >> *index2;
            //cout<<*index2<<endl;
            (*v1).y = *index2;
            //cout<<(*v1).y<<endl;
            delete stream2;
            delete index2;
            delete s2;
            
            istringstream *stream3 = new istringstream();
            (*stream3).str(*s3);
            float *index3 = new float();
            (*stream3) >> *index3;
            (*v1).z = *index3;
            delete stream3;
            delete index3;
            delete s3;
            
            //cout<<(*v1).x<<" "<<(*v1).y<<" "<<(*v1).z<<endl;
            
            //int id = kk;
            //cout<<kk-1<<endl;
            nMaterialPoint[kk-1].mtlKs.push_back(*v1);
            sin.clear();
            delete v1;
        }
        
      
        if((*everyLine)[0] == 'i'){//illum
            istringstream sin(*everyLine);
            string *s1 = new string();
            sin>>*str>>*s1;
            
            istringstream *stream1 = new istringstream();
            (*stream1).str(*s1);
            int *index1 = new int();
            *stream1 >> *index1;
            
            nMaterialPoint[kk-1].mtlIllum = *index1;
            //cout<<kk-1<<endl;
            //cout<<*index1<<endl;
            
            sin.clear();
            delete stream1;
            delete index1;
        }
        
        if((*everyLine)[0] == 'd'){//d
            istringstream sin(*everyLine);
            string *s1 = new string();
            sin>>*str>>*s1;
            
            istringstream *stream1 = new istringstream();
            (*stream1).str(*s1);
            float *index1 = new float();
            (*stream1) >> *index1;
            
            nMaterialPoint[kk-1].mtlD = *index1;
            //cout<<*index1<<endl;
            sin.clear();
            delete index1;
            delete stream1;
        }
        
        if((*everyLine)[0] == 'N' && (*everyLine)[1] == 's'){//Ns
            istringstream sin(*everyLine);
            string *s1 = new string();
            sin>>*str>>*s1;
            
            //cout<<s1<<endl;
            
            istringstream *stream1 = new istringstream();
            (*stream1).str(*s1);
            float *index1 = new float();
            (*stream1) >> *index1;
            
            nMaterialPoint[kk-1].mtlNs = *index1;
            //cout<<*index1<<endl;
            delete stream1;
            delete index1;
            sin.clear();
        }
    }
    fin2.close();
    delete everyLine;
    delete str;
    /*vector<tagMaterial>::iterator it;
    for(it = nMaterialPoint.begin(); it != nMaterialPoint.end(); it++){
        cout<<(*it).mtlName<<endl;
    }*/
}

void tag3DModel::draw(){//画出图形
    
   

    for(int i = 0; i < groupSet.size(); i++){//一个组一个组画
        
        //int groupId = i;
        
        //cout<<groupId<<endl;
        
        if(groupSet[i].hasMat == true){//有材质的组进行贴材质
            
            //cout<<groupSet[i].groupName<<endl;
            
            for(int m = 0; m < nMaterialPoint.size(); m++){
                //cout<<"*****"<<nMaterialPoint[m].mtlName<<endl;
                if(groupSet[i].groupName == nMaterialPoint[m].mtlName){
                    
                    //cout<<m<<endl;
                    //cout<<i<<"*"<<groupSet[i].groupName<<"-"<<nMaterialPoint[m].mtlName<<endl;
                    
                    GLfloat ambient[4] = {0};
                    GLfloat diffuse[4] = {0};
                    GLfloat specular[4] = {0};
                    GLfloat shininess[1] = {0};
                    
                    if(nMaterialPoint[m].mtlKa.size()!= 0){
                        ambient[0] = nMaterialPoint[m].mtlKa[0].x;
                        ambient[1] = nMaterialPoint[m].mtlKa[0].y;
                        ambient[2] = nMaterialPoint[m].mtlKa[0].z;
                        if(nMaterialPoint[m].mtlD != 1.0){
                            ambient[3] = nMaterialPoint[m].mtlD;
                        }else{
                            ambient[3] = 1.0;
                        }
                        //cout<<ambient[0]<<"*"<<ambient[1]<<"*"<<ambient[2]<<"*"<<ambient[3]<<endl;
                    }
                    
                    if(nMaterialPoint[m].mtlKd.size()!= 0){
                        diffuse[0] = nMaterialPoint[m].mtlKd[0].x;
                        diffuse[1] = nMaterialPoint[m].mtlKd[0].y;
                        diffuse[2] = nMaterialPoint[m].mtlKd[0].z;
                        if(nMaterialPoint[m].mtlD != 1.0){
                            diffuse[3] = nMaterialPoint[m].mtlD;
                        }else{
                            diffuse[3] = 1.0;
                        }
                        //cout<<diffuse[0]<<"*"<<diffuse[1]<<"*"<<diffuse[2]<<"*"<<diffuse[3]<<endl;
                    }
                    
                    if(nMaterialPoint[m].mtlKs.size()!= 0){
                        specular[0] = nMaterialPoint[m].mtlKs[0].x;
                        specular[1] = nMaterialPoint[m].mtlKs[0].y;
                        specular[2] = nMaterialPoint[m].mtlKs[0].z;
                        if(nMaterialPoint[m].mtlD != 1.0){
                            specular[3] = nMaterialPoint[m].mtlD;
                        }else{
                            specular[3] = 1.0;
                        }
                    }
                    
                    if(nMaterialPoint[m].mtlNs){
                        shininess[0] = nMaterialPoint[m].mtlNs;
                    }
                    
                    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
                    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
                    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    //glMaterialfv(GL_FRONT, GL_EMISSION, diffuse);
                    
                    //glColorMaterial(GL_FRONT, GL_AMBIENT);
                    //glEnable(GL_COLOR_MATERIAL);
                    
                    memset(ambient, 0, 4 * sizeof(GLfloat));
                    memset(diffuse, 0, 4 * sizeof(GLfloat));
                    memset(specular, 0, 4 * sizeof(GLfloat));
                    memset(shininess, 0, 1 * sizeof(GLfloat));
                    
                    //break;
                    
                }
            }
        }
      
        
        for(int j = 0; j < groupSet[i].groupFace.size(); j++){
           
            glBegin(GL_POLYGON);
            
            for(int k = 0; k < groupSet[i].groupFace[j].oneFaceVertexIndex.size(); k++){
                
                //cout<<k<<endl;
                
                if(nNormalsPoint.size() != 0){//有法线
                    int *index2 = new int();
                    *index2 = groupSet[i].groupFace[j].oneFaceNormalIndex[k];
                    //cout<<*index2<<endl;
                    glNormal3f(nNormalsPoint[*index2-1].x, nNormalsPoint[*index2-1].y, nNormalsPoint[*index2-1].z);
                    //cout<<nNormalsPoint[*index2-1].x<<" "<<nNormalsPoint[*index2-1].y<<" "<<nNormalsPoint[*index2-1].z<<endl;
                    delete index2;
                }
                
                int *index = new int();
                *index = groupSet[i].groupFace[j].oneFaceVertexIndex[k];
                glVertex3f(nVertexsPoint[*index-1].x, nVertexsPoint[*index-1].y, nVertexsPoint[*index-1].z);
                //cout<<nVertexsPoint[*index-1].x<<" "<<nVertexsPoint[*index-1].y<<" "<<nVertexsPoint[*index-1].z<<endl;
                delete index;
                
            }
            
            glEnd();
        }
        //cout<<endl;
        
        
        
    }
}


   


