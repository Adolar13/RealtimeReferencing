#pragma once
#include "RefObject.h"
#include "gencam.h"

class RefCam :
	public RefObject
{
public:
	RefCam();
	~RefCam();

	float nearC;
	float farC;
	float lens;


	GenCamera* createCam();
};

