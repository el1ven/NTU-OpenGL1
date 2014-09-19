//
//  main.cpp
//  proGL
//
//  Created by el1ven on 2/9/14.
//  Copyright (c) 2014 el1ven. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <vector>
#include "Vector3.h"
#include "tag3DModel.h"
#include <iostream>
#include <string>
#include <GLUI/GLUI.h>
#include <math.h>
#include<stdlib.h>

#define M_PI 3.14

using namespace std;

GLUI *glui;
GLUI_Panel *obj_panel;
int   main_window;

tag3DModel *obj = new tag3DModel();

/**************************************** 用于鼠标拖拽 *************/
float angle = 0.0f;//旋转角度
Vector3 lastPos;//上一次移动的坐标值和当前的坐标值
Vector3 axis;//计算相对于轴的信息
int curX, curY = 0;//当前鼠标的坐标
int startX, startY = 0;//鼠标没有按下时的坐标
int winWidth, winHeight;
bool trackingMouse = false;
bool redrawContinue = false;
bool trackballMove = false;

/**************************************** 用于鼠标拖拽 *************/



void init(){

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    GLfloat ambient[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat position[] = {-300.0f, 300.0f, 300.0f, 0.0f};
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);//指定深度比较中使用的数值
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat light_position[] = { 0.0, 50.0, 300.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
}


void myGlutIdle( void )
{
    /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
    if (glutGetWindow() != main_window){
        glutSetWindow(main_window);
    }
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutPostRedisplay();
}


/**************************************** myGlutReshape() *************/

void myGlutReshape( int x, int y )
{
    winWidth = x;
    winHeight =y;
    
    float xy_aspect;
    xy_aspect = (float)x / (float)y;
    glViewport( 0, 0, x, y );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60, xy_aspect, 0.3,3000);
    gluLookAt(0, 0, 120*xy_aspect, 0, 0, 0, 0, 1, 0);
    //glFrustum( -xy_aspect*.8, xy_aspect*.8, -.08, .08, .1, 60.0 );
    
    
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    //glScalef(2.0, 2.0, 2.0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRotatef(angle*100, axis.x, axis.y, axis.z);
    //cout<<angle<<"*"<<axis.x<<"*"<<axis.y<<"*"<<axis.z<<endl;
    obj->draw();
    glutSwapBuffers();
}

/***************************************** 鼠标拖拽 *****************/

Vector3 trackBall(int x, int y, int width, int height, Vector3 v){
    //project x,y onto a hemisphere centered within width,height
    float d, r;
    v.x = (2.0f*x - width)/width;
    v.y = (height - 2.0f*y)/height;
    d = (float) sqrt (v.x*v.x + v.y*v.y);
    v.z = (float) cos((M_PI/2.0F) * ((d < 1.0F) ? d : 1.0F));
    r = 1.0f / (float) sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    
    v.x *= r;//坐标映射
    v.y *= r;
    v.z *= r;
    //cout<<v.x<<v.y<<v.z<<endl;
    return v;
}

void mouseMotion(int x, int y){
    Vector3 currentPos;
    currentPos = trackBall(x, y, winWidth, winHeight, currentPos);
    //cout<<currentPos.x<<endl;
    float dx, dy, dz = 0.0f;//差值距离
    
       if(trackingMouse){
        dx = currentPos.x - lastPos.x;//计算差向量
        dy = currentPos.y - lastPos.y;
        dz = currentPos.z - lastPos.z;
        
        //cout<<dx<<dy<<dz<<endl;
        
        if(dx||dy||dz){//三者不能同时为0，否则相当于没动
            angle = 90.0f*sqrt(dx*dx+dy*dy+dz*dz);
            
            //计算差积，得到旋转轴
            axis.x = lastPos.y*currentPos.z - lastPos.z*currentPos.y;
            axis.y = lastPos.z*currentPos.x - lastPos.x*currentPos.z;
            axis.z = lastPos.x*currentPos.y - lastPos.y*currentPos.x;
            
            lastPos.x = currentPos.x;//更新信息
            lastPos.y = currentPos.y;
            lastPos.z = currentPos.z;
        }
    }
    //glutPostRedisplay();
}

void startMotion(int x, int y){
    trackingMouse = true;
    redrawContinue = false;
    startX = x;
    startY = y;
    trackBall(x, y, winWidth, winHeight, lastPos);
    trackballMove = true;
}

void stopMotion(int x, int y){
    trackingMouse = false;
    if(startX != x || startY != y){
        redrawContinue = true;
    }else{
        angle = 0.0f;
        redrawContinue = false;
        trackingMouse = false;
    }
}

void spin() {
    if (redrawContinue)
        glutPostRedisplay();
}




void myGlutMouse(int button, int state, int x, int y)
{
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN){
                y = winHeight-y;
                startMotion(x, y);
                break;
            }
            if(state == GLUT_UP){
                stopMotion(x, y);
                break;
            }

        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN){
                exit(0);
            }
            break;
        default:
            break;
    }
    
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 500, 500 );
    main_window = glutCreateWindow( "Mesh Viewer" );
    init();
    obj->parseMtl("/Users/el1ven/Desktop/obj/porsche.mtl");
    obj->parse("/Users/el1ven/Desktop/obj/porsche.obj");
    //obj->parse("/Users/el1ven/Desktop/obj/al.obj");
    //obj->parseMtl("/Users/el1ven/Desktop/obj/al.mtl");
    //obj->parse("/Users/el1ven/Desktop/obj/rose+vase.obj");
    //obj->parseMtl("/Users/el1ven/Desktop/obj/rose+vase.mtl");
    //obj->parse("/Users/el1ven/Desktop/obj/flowers.obj");
    //obj->parseMtl("/Users/el1ven/Desktop/obj/flowers.mtl");
    //obj->parse("/Users/el1ven/Desktop/obj/soccerball.obj");
    //obj->parseMtl("/Users/el1ven/Desktop/obj/soccerball.mtl");
    //glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
    
    
    
    
    glutReshapeFunc( myGlutReshape );
    glutDisplayFunc( myGlutDisplay );
    glutIdleFunc( spin );
    glutMouseFunc( myGlutMouse );
    glutMotionFunc( mouseMotion );
    
    
    
    
    /*
     //create glui user interface
     GLUI *glui = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_RIGHT);
     
     //obj_panel = new GLUI_Rollout(glui, "Properties", false );
     glui->add_statictext( "Mesh Viewer Options:" );
     
     //glui->set_main_gfx_window( main_window );
     
     //GLUI_Master.set_glutIdleFunc( myGlutIdle );*/
    
    glutMainLoop();
    return 0;
}

