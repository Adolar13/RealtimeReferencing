#pragma once
#include "RefObject.h"
#include "genlight.h"
class RefLight :
	public RefObject
{
public:
	RefLight();
	RefLight(float b, float a, float d, float i);
	~RefLight();

	float blend;
	float angle;
	float distance;
	float intensity;

	GenLight* createSpot();

};

