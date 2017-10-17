#pragma once

#define _USE_MATH_DEFINES

#include "resource.h"
#include "RefObject.h"
#include "RefLight.h"
#include "RefCam.h"
#include "RefScene.h"
#include "RefGeom.h"

#include "include\rapidjson\reader.h"
#include "include\rapidjson\document.h"

#include <istdplug.h>
#include <imenus.h>
#include <imenuman.h>
#include <maxtypes.h>
#include <math.h>

extern TCHAR *GetString(int id);


class SceneController
{

	static SceneController* m_instance;
	SceneController();

public:
	void Print(wchar_t * c);
	void CreateObjectNode(RefObject * ro);
	TriObject * CreateTriObject();
	RefObject * CreateRefObjectFromFile(const char * name);
	RefGeom * CreateRefGeomFromFile(const char * name);
	RefLight * CreateRefLightFromFile(const char * name);
	RefCam * CreateRefCamFromFile(const char * name);
	bool CreateRefScene(const char * path);

	bool CreateAllFromRefRoot(const char * path);

	bool CreateRefChilds(rapidjson::Value & val, RefObject * parent);

	char* refPath = nullptr;



	RefObject* CreateFromDomElem(rapidjson::Value & val);

	RefLight* CreateLightObj(rapidjson::Value & val);

	RefCam * CreateCamObj(rapidjson::Value & val);

	RefGeom* CreateMeshObj(rapidjson::Value & val);

	void Update(const char * name);

	bool DeleteRefScene();

	void DeleteNode(RefObject * obj, bool keepChilds);







	///////////////
	//FOR TESTING//
	///////////////
	void TestFunction();

	///////////////

	static SceneController * Instance() {
		if (!m_instance)
			m_instance = new SceneController;
		return m_instance;
	}

private:


	float to_radians(float degrees);
	wchar_t * to_wchar(char * s);
};

