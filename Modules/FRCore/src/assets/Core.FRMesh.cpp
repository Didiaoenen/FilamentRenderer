#include "Core.FRMesh.h"

FR::FRMesh::~FRMesh()
{
	vertexs.clear();
	indices.clear();

	positions.clear();
	tangents.clear();
	normals.clear();
	colors.clear();
	texCoords0.clear();
	texCoords1.clear();

	jointIndexs.clear();
	jointWeights.clear();

	jointRemaps.clear();
	inverseBindPoses.clear();
}
