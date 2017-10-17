#include "RefCam.h"



RefCam::RefCam()
{
}


RefCam::~RefCam()
{
}

GenCamera * RefCam::createCam()
{
	TimeValue t(0);

	GenCamera* obj = (GenCamera*)GetCOREInterface()->CreateInstance(CAMERA_CLASS_ID, Class_ID(SIMPLE_CAM_CLASS_ID, 0));
	obj->SetType(0);
	obj->SetFOV(t, lens);
	obj->SetManualClip(1);
	obj->SetClipDist(t, CAM_HITHER_CLIP, nearC);
	obj->SetClipDist(t, CAM_YON_CLIP, farC);
	
	return obj;
}
