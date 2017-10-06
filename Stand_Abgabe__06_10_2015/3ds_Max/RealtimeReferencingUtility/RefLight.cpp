#include "RefLight.h"



RefLight::RefLight()
{
}

RefLight::RefLight(float b, float a, float d, float i)
{
	blend = b;
	angle = a;
	distance = d;
	intensity = i;
}




RefLight::~RefLight()
{
}

GenLight* RefLight::createSpot()
{
	TimeValue t(0);

	GenLight* obj = (GenLight*)GetCOREInterface()->CreateInstance(LIGHT_CLASS_ID, Class_ID(FSPOT_LIGHT_CLASS_ID, 0));
	obj->SetDecayType(2);
	obj->SetDecayRadius(t, distance);
	obj->SetIntensity(t, intensity);
	float hotspot = angle * (1 - blend);
	if (hotspot > (angle - 2))
		hotspot = angle - 2;
	obj->SetHotspot(t, hotspot);
	obj->SetFallsize(t, angle);

	return obj;
}
