//
//  Vector3.h
//  proGL
//
//  Created by el1ven on 29/8/14.
//  Copyright (c) 2014 el1ven. All rights reserved.
//

#ifndef __proGL__Vector3__
#define __proGL__Vector3__


//Vecotr3.h
#pragma once
#include <iostream>

extern const double uZero;

using namespace std;

class Vector3
{
	
public:
    float x, y, z = 0.0f;
	Vector3():x(0), y(0), z(0){}
	Vector3(float x1, float y1, float z1):x(x1), y(y1), z(z1){}
	Vector3(const Vector3 &v);
	~Vector3();
	void operator=(const Vector3 &v);
	Vector3 operator+(const Vector3 &v);
	Vector3 operator-(const Vector3 &v);
	Vector3 operator/(const Vector3 &v);
	Vector3 operator*(const Vector3 &v);
	Vector3 operator+(float f);
	Vector3 operator-(float f);
	Vector3 operator/(float f);
	Vector3 operator*(float f);
	float dot(const Vector3 &v);
	float length();
	void normalize();
	Vector3 crossProduct(const Vector3 &v);
	void printVec3();
};

#endif /* defined(__proGL__Vector3__) */
