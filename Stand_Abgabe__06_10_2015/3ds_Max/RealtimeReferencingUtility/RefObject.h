#pragma once

#include <vector>

#include <maxtypes.h>
#include <triobj.h>
#include <polyobj.h>
#include <mnmesh.h>

class RefObject
{
public:
	RefObject();
	~RefObject();

	INode * refNode;

	Point3 position;
	Point3 rotation;
	const char* name;
	char objType;

	std::vector<RefObject*> childs;
	RefObject* parent;


};

