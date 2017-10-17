#pragma once
#include "RefObject.h"
class RefGeom :
	public RefObject
{
public:
	RefGeom();
	~RefGeom();

	TriObject * BuildTriMesh(void);

	PolyObject * BuildPolyMesh(void);





	void AddPoint(float x, float y, float z);


	std::vector<Point3> points;
	std::vector<Point3> normals;
	std::vector<int> triangleVertIndices;
	std::vector<std::vector<int>> polys;
};

