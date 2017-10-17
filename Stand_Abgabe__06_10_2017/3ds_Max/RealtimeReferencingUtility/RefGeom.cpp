#include "RefGeom.h"


RefGeom::RefGeom() {

}


RefGeom::~RefGeom()
{
}


TriObject *RefGeom::BuildTriMesh(void)
{

	TriObject *triobj = CreateNewTriObject();
	if (triobj == NULL)
		return NULL;

	// TODO: ERROR Handling
	//Check if all points have normals
	if (points.size() != normals.size())
		//return NULL;
		//Check if all triangles have 3 Vertices
		if (triangleVertIndices.size() % 3 != 0)
			return NULL;

	int numVerts = (int)points.size();
	int numFaces = (int)triangleVertIndices.size() / 3;
	Mesh &mesh = triobj->GetMesh();

	// Vert positions
	mesh.setNumVerts(numVerts);
	for (int i = 0; i < numVerts; i++)
		mesh.setVert(i, points[i]);

	//Faces
	mesh.setNumFaces(numFaces);
	//normalSpec->SetNumFaces(numTriangles);
	//map.setNumFaces(numTriangles);
	for (int i = 0, j = 0; i < numFaces; i++, j += 3)
	{
		// three vertex indices of a triangle
		int v0 = triangleVertIndices[j];
		int v1 = triangleVertIndices[j + 1];
		int v2 = triangleVertIndices[j + 2];

		// vertex positions
		Face &face = mesh.faces[i];
		face.setMatID(1);
		face.setEdgeVisFlags(1, 1, 1);
		face.setVerts(v0, v1, v2);
	}

	mesh.InvalidateGeomCache();
	mesh.InvalidateTopologyCache();

	return triobj;
}

PolyObject *RefGeom::BuildPolyMesh(void) {
	PolyObject *polyobj = CreateEditablePolyObject();
	MNMesh &mesh = polyobj->GetMesh();

	int numVerts = (int)points.size();
	int numFaces = (int)polys.size();


	//Verts
	//mesh.setNumVerts(numVerts);
	for (int i = 0; i < numVerts; i++)
		mesh.NewVert(points[i]);

	//Faces
	mesh.setNumFaces(numFaces);
	for (int i = 0; i < numFaces; i++) {
		int size = polys[i].size();
		int * data = polys[i].data();
		mesh.CreateFace(size, data);
	}

	mesh.InvalidateGeomCache();

	return polyobj;

}

void RefGeom::AddPoint(float x, float y, float z) {
	this->points.push_back(Point3(x, y, z));
}