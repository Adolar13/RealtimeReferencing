#include "SceneController.h"


#define RefRoot RefScene::Instance()->root

SceneController *SceneController::m_instance = 0;


SceneController::SceneController()
{
}

void SceneController::Print(wchar_t* c){
	GetCOREInterface()->PushPrompt(c);
}


void SceneController::CreateObjectNode(RefObject* ro) {

	/*
	PolyObject* polyobj = (PolyObject*)ro->BuildObj();
	INode* node = GetCOREInterface()->CreateObjectNode(polyobj);
	TimeValue t(0);
	Matrix3 tm(1);
	node->SetNodeTM(t, tm);
	GetCOREInterface()->RedrawViews(t);
	*/
}


TriObject* SceneController::CreateTriObject() {
	TriObject* tri = new TriObject();
	Mesh& mesh = tri->GetMesh();
	mesh.setNumVerts(3);
	mesh.setNumFaces(1);

	mesh.setVert(0, Point3(0, 0, 0));
	mesh.setVert(1, Point3(10, 10, 0));
	mesh.setVert(2, Point3(20, 0, 0));

	mesh.faces[0].setVerts(0, 1, 2);
	mesh.faces[0].setEdgeVisFlags(EDGE_VIS, EDGE_VIS, EDGE_VIS);

	mesh.InvalidateGeomCache();

	return tri;
}


RefObject* SceneController::CreateRefObjectFromFile(const char* name) {
	return nullptr;
}

RefGeom* SceneController::CreateRefGeomFromFile(const char* name) {
	using namespace rapidjson;

	std::string filePath = std::string(Instance()->refPath) + std::string("/") + std::string(name) + std::string(".json");
	// Read whole file into a buffer
	FILE* fp = fopen(filePath.c_str(), "r");
	if (fp == nullptr) {
		GetCOREInterface()->PushPrompt(L"File Not Found");
		return nullptr;
	}
	fseek(fp, 0, SEEK_END);
	size_t filesize = (size_t)ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buffer = (char*)malloc(filesize + 1);
	size_t readLength = fread(buffer, 1, filesize, fp);
	buffer[readLength] = '\0';
	fclose(fp);
	// In situ parsing the buffer into d, buffer will also be modified
	Document d;
	d.ParseInsitu(buffer);
	// Query/manipulate the DOM here...

	if (d.HasMember("verts")) {
		RefGeom* ro = new RefGeom();
		float x = 0, y = 0, z = 0;
		GetCOREInterface()->PushPrompt(L"Has Verts");
		const rapidjson::Value& verts = d["verts"];
		for (rapidjson::Value::ConstValueIterator itr = verts.Begin(); itr != verts.End(); itr++) {
			x = (*itr)["x"].GetFloat();
			y = (*itr)["y"].GetFloat();
			z = (*itr)["z"].GetFloat();
			ro->AddPoint(x, y, z);
		}
		if (d.HasMember("faces")) {
			const rapidjson::Value& faces = d["faces"];
			for (int j = 0; j < faces.Size(); j++) {
				std::vector<int> tmp;
				for (int i = 0; i < faces[j]["verts"].Size(); i++) {
					int tvi = faces[j]["verts"][i].GetInt();
					tmp.push_back(tvi);
				}
				ro->polys.push_back(tmp);
			}
		}
		return ro;
	}


	return nullptr;

	free(buffer);
	// Note: At this point, d may have dangling pointers pointed to the deallocated buffer.
}

RefLight* SceneController::CreateRefLightFromFile(const char* name) {
	using namespace rapidjson;

	std::string filePath = std::string(Instance()->refPath) + std::string("/") + std::string(name) + std::string(".json");
	// Read whole file into a buffer
	FILE* fp = fopen(filePath.c_str(), "r");
	if (fp == nullptr) {
		GetCOREInterface()->PushPrompt(L"File Not Found");
		return nullptr;
	}
	fseek(fp, 0, SEEK_END);
	size_t filesize = (size_t)ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buffer = (char*)malloc(filesize + 1);
	size_t readLength = fread(buffer, 1, filesize, fp);
	buffer[readLength] = '\0';
	fclose(fp);
	// In situ parsing the buffer into d, buffer will also be modified
	Document d;
	d.ParseInsitu(buffer);
	// Query/manipulate the DOM here...
	RefLight* rl = new RefLight();

	if (d.HasMember("intensity")) 
		rl->intensity = d["intensity"].GetFloat();

	if (d.HasMember("blend"))
		rl->blend = d["blend"].GetFloat();

	if (d.HasMember("angle"))
		rl->angle = d["angle"].GetFloat();

	if (d.HasMember("distance"))
		rl->distance = d["distance"].GetFloat();

	return rl;

	free(buffer);
}

RefCam * SceneController::CreateRefCamFromFile(const char * name)
{
	using namespace rapidjson;

	std::string filePath = std::string(Instance()->refPath) + std::string("/") + std::string(name) + std::string(".json");
	// Read whole file into a buffer
	FILE* fp = fopen(filePath.c_str(), "r");
	if (fp == nullptr) {
		GetCOREInterface()->PushPrompt(L"File Not Found");
		return nullptr;
	}
	fseek(fp, 0, SEEK_END);
	size_t filesize = (size_t)ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buffer = (char*)malloc(filesize + 1);
	size_t readLength = fread(buffer, 1, filesize, fp);
	buffer[readLength] = '\0';
	fclose(fp);
	// In situ parsing the buffer into d, buffer will also be modified
	Document d;
	d.ParseInsitu(buffer);
	// Query/manipulate the DOM here...
	RefCam* rc = new RefCam();

	if (d.HasMember("far"))
		rc->farC = d["far"].GetFloat();

	if (d.HasMember("near"))
		rc->nearC = d["near"].GetFloat();

	if (d.HasMember("lens"))
		rc->lens = d["lens"].GetFloat();

	return rc;

	free(buffer);
}



bool SceneController::CreateRefScene(const char* path) {
	if (Instance()->refPath == nullptr) {
		Instance()->refPath = new char[strlen(path)];
		strncpy(Instance()->refPath, path, strlen(path) + 1);
	}

	if (RefRoot == nullptr) {
		RefRoot = new RefObject();
		RefRoot->parent = nullptr;
		Object* obj = (Object*)GetCOREInterface()->CreateInstance(HELPER_CLASS_ID, Class_ID(POINTHELP_CLASS_ID,0));
		RefRoot->refNode = GetCOREInterface()->CreateObjectNode(obj);
		RefRoot->refNode->SetName(L"_RealtimeReferencingRoot");
		RefRoot->refNode->Freeze(true);

		Instance()->CreateAllFromRefRoot(path);

		TimeValue t(0);
		GetCOREInterface()->RedrawViews(t);
		return true;
	}
	else {
		return false;
	}
}

bool SceneController::CreateAllFromRefRoot(const char* path) {
	using namespace rapidjson;

	std::string filePath = std::string(path) + std::string("/") + std::string("_refRoot.json");
	// Read whole file into a buffer
	FILE* fp = fopen(filePath.c_str(), "r");
	if (fp == nullptr) {
		GetCOREInterface()->PushPrompt(L"File Not Found");
		return nullptr;
	}
	fseek(fp, 0, SEEK_END);
	size_t filesize = (size_t)ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buffer = (char*)malloc(filesize + 1);
	size_t readLength = fread(buffer, 1, filesize, fp);
	buffer[readLength] = '\0';
	fclose(fp);
	// In situ parsing the buffer into d, buffer will also be modified
	Document d;
	d.ParseInsitu(buffer);
	// Query/manipulate the DOM here...
	RefObject* ro = nullptr;
	for (SizeType i = 0; i < d.Size(); i++) {
		// Store the value of the element in a vector.
		if (d[i].HasMember("refType")) {
			ro = Instance()->CreateFromDomElem(d[i]);
			ro->position = Point3(d[i]["location"][0].GetFloat(), d[i]["location"][1].GetFloat(), d[i]["location"][2].GetFloat());
			ro->rotation = Point3(d[i]["rotation"][0].GetFloat(), d[i]["rotation"][1].GetFloat(), d[i]["rotation"][2].GetFloat());
			ro->name = d[i]["name"].GetString();
			Object* o = nullptr;
			char c = ro->objType;
			switch(c) {
				case 'M':
					o = ((RefGeom*)ro)->BuildPolyMesh();
					break;
				case 'L':
					o = ((RefLight*)ro)->createSpot();
					break;
				case 'C':
					o = ((RefCam*)ro)->createCam();
					break;
				default:
					o = (Object*)GetCOREInterface()->CreateInstance(HELPER_CLASS_ID, Class_ID(POINTHELP_CLASS_ID, 0));
					break;
			}
			RefRoot->childs.push_back(ro);
			ro->parent = RefRoot;
			INode* node = GetCOREInterface()->CreateObjectNode(o);
			ro->refNode = node;
			node->SetName(to_wchar((char*)ro->name));
			RefRoot->refNode->AttachChild(node);
			TimeValue t(0);
			Matrix3 tm(1);
			tm.SetRotate(Quat().SetEuler(to_radians(ro->rotation.x), to_radians(ro->rotation.y), to_radians(ro->rotation.z)));
			tm.SetTrans(ro->position);
			node->SetNodeTM(t, tm);

			if (d[i].HasMember("childs")) {
				Instance()->CreateRefChilds(d[i]["childs"], ro);
			}
			GetCOREInterface()->RedrawViews(t);
		}
	}
	return true;

	free(buffer);
	// Note: At this point, d may have dangling pointers pointed to the deallocated buffer.
}

bool SceneController::CreateRefChilds(rapidjson::Value& val, RefObject* parent) {
	using namespace rapidjson;

	RefObject* ro = nullptr;
	for (SizeType i = 0; i < val.Size(); i++) {
		// Store the value of the element in a vector.
		if (val[i].HasMember("refType")) {
			ro = Instance()->CreateFromDomElem(val[i]);
			ro->position = Point3(val[i]["location"][0].GetFloat(), val[i]["location"][1].GetFloat(), val[i]["location"][2].GetFloat());
			ro->rotation = Point3(val[i]["rotation"][0].GetFloat(), val[i]["rotation"][1].GetFloat(), val[i]["rotation"][2].GetFloat());
			ro->name = val[i]["name"].GetString();
			Object* o = nullptr;
			char c = ro->objType;
			switch (c) {
			case 'M':
				o = ((RefGeom*)ro)->BuildPolyMesh();
				break;
			case 'L':
				o = ((RefLight*)ro)->createSpot();
				break;
			case 'C':
				o = ((RefCam*)ro)->createCam();
				break;
			}
			parent->childs.push_back(ro);
			ro->parent = parent;
			INode* node = GetCOREInterface()->CreateObjectNode(o);
			ro->refNode = node;
			node->SetName(to_wchar((char*)ro->name));
			parent->refNode->AttachChild(node);
			TimeValue t(0);
			Matrix3 tm(1);
			tm.SetRotate(Quat().SetEuler(to_radians(ro->rotation.x), to_radians(ro->rotation.y), to_radians(ro->rotation.z)));
			tm.SetTrans(ro->position);
			node->SetNodeTM(t, tm);

			if (val[i].HasMember("childs")) {
				Instance()->CreateRefChilds(val[i]["childs"], ro);
			}
		}
	}
	return true;

	// Note: At this point, d may have dangling pointers pointed to the deallocated buffer.
}

RefObject* SceneController::CreateFromDomElem(rapidjson::Value& val) {
	const char* type = val["refType"].GetString();
	RefObject* ro;
	switch (type[0]) {
		case 'M':
			ro = Instance()->CreateMeshObj(val);
			ro->objType = type[0];
			break;
		case 'L':
			ro = Instance()->CreateLightObj(val);
			ro->objType = type[0];
			break;
		case 'C':
			ro = Instance()->CreateCamObj(val);
			ro->objType = type[0];
			break;
		default:
			ro = new RefObject();
			ro->objType = 'E';
	}
	return ro;
}

RefLight* SceneController::CreateLightObj(rapidjson::Value& val) {
	TimeValue t(0);
	RefLight *l = Instance()->CreateRefLightFromFile(val["name"].GetString());
	return l;
}

RefCam* SceneController::CreateCamObj(rapidjson::Value& val) {
	TimeValue t(0);
	RefCam* c = Instance()->CreateRefCamFromFile(val["name"].GetString());

	return c;
}

RefGeom* SceneController::CreateMeshObj(rapidjson::Value& val) {
	TimeValue t(0);
	RefGeom* r = Instance()->CreateRefGeomFromFile(val["name"].GetString());

	return r;

	/*
	if (RefRoot->childs.size() != 0) {
		RefRoot->childs[0]->refNode->Delete(t, true);
		RefRoot->childs.pop_back();
	}
	RefRoot->childs.push_back(r);
	PolyObject* polyobj = r->BuildPolyMesh();
	INode* node = GetCOREInterface()->CreateObjectNode(polyobj);
	Matrix3 tm(1);
	node->SetNodeTM(t, tm);
	GetCOREInterface()->RedrawViews(t);
	r->refNode = node;
	RefRoot->refNode->AttachChild(r->refNode, 1);

	Instance()->Print(L"Mesh Obj created");

	return true;
	*/
}

bool SceneController::DeleteRefScene() {
	if (RefRoot != nullptr) {
		TimeValue t(0);
		Instance()->DeleteNode(RefRoot, false);
		RefRoot = nullptr;
		return true;
	}
	else {
		return false;
	}
}

void SceneController::DeleteNode(RefObject* obj, bool keepChilds) {
	TimeValue t(0);
	int childs = obj->childs.size();
	if (childs != 0) {
		if (keepChilds)
			for (int i = 0; i < childs; i++) {
				obj->refNode->GetParentNode()->AttachChild(obj->refNode->GetChildNode(i));
			}
		else 
			for (int i = 0; i < childs; i++) {
				Instance()->DeleteNode(obj->childs[i], keepChilds);
			}
	}
	obj->refNode->Delete(t, 0);
}

///////////////
//FOR TESTING//
///////////////
void SceneController::TestFunction() {

	/*
	RefObject* ro = new RefObject();
	Object* obj_one = (Object*)GetCOREInterface()->CreateInstance(HELPER_CLASS_ID, Class_ID(POINTHELP_CLASS_ID, 0));
	ro->refNode = GetCOREInterface()->CreateObjectNode(obj_one);

	RefObject* child = new RefObject();
	Object* obj_two = (Object*)GetCOREInterface()->CreateInstance(HELPER_CLASS_ID, Class_ID(POINTHELP_CLASS_ID, 0));
	child->refNode = GetCOREInterface()->CreateObjectNode(obj_two);

	RefObject* childTwo = new RefObject();
	Object* obj_three = (Object*)GetCOREInterface()->CreateInstance(HELPER_CLASS_ID, Class_ID(POINTHELP_CLASS_ID, 0));
	childTwo->refNode = GetCOREInterface()->CreateObjectNode(obj_three);

	ro->childs.push_back(child);
	ro->refNode->AttachChild(child->refNode);

	child->childs.push_back(childTwo);
	child->refNode->AttachChild(childTwo->refNode);

	child->parent = ro;
	childTwo->parent = child;

	DeleteNode(child->refNode, false);
	delete child;
	*/
}
///////////////
///////////////


void SceneController::Update(const char* name) {
	TimeValue t(0);
	if (strcmp(name, "_refRoot.json") == 0 ) {
		Instance()->DeleteRefScene();
		Instance()->CreateRefScene(Instance()->refPath);
	}
	else {

	}
	

}

float SceneController::to_radians(float degrees) {
	return degrees * (M_PI / 180);
}

wchar_t* SceneController::to_wchar(char* s) {
	const size_t cSize = strlen(s) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, s, cSize);

	return wc;
}