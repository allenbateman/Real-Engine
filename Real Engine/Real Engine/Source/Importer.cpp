#include "Importer.h"

Importer::Importer()
{
}

Importer::~Importer()
{
}

void Importer::ImportMaterial(const aiMaterial* material, Material* ourMaterial)
{
	// ourMaterial->textures = material->textures
}

uint64 Importer::SaveMaterial(const Material* ourMaterial, char** fileBuffer)
{
	ILuint size;
	ILubyte* data;
	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use
	size = ilSaveL(IL_DDS, nullptr, 0); // Get the size of the data buffer
	if (size > 0) {
		data = new ILubyte[size]; // allocate data buffer
		if (ilSaveL(IL_DDS, data, size) > 0) // Save to buffer with the ilSaveIL function
			*fileBuffer = (char*)data;
			RELEASE_ARRAY(data);
	}
	return uint64();
}

void Importer::LoadMaterial(const char** fileBuffer, Material* ourMaterial)
{
}

uint64 Importer::SaveMesh(Mesh mesh)
{
	// amount of indices / vertices / colors / normals / texture_coords / AABB
	int numIndices = mesh.indices.size();
	int numVertices = mesh.vertices.size();


	uint ranges[2] = { numIndices,  numVertices };
	
	uint size = sizeof(ranges) + sizeof(uint) * numIndices + sizeof(float) * numVertices * 3;
	char* fileBuffer = new char[size]; // Allocate
	char* cursor = fileBuffer;
	uint bytes = sizeof(ranges); // First store ranges
	memcpy(cursor, ranges, bytes);
	cursor += bytes;
	// Store indices
	bytes = sizeof(uint) * numIndices;
	memcpy(cursor, (void*)numIndices, bytes);
	cursor += bytes;

	return uint64();
}
