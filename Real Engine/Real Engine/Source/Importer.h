#include "Application.h"
#include "assimp/scene.h"
#include "Material.h"
#include "il.h"
#include "Mesh.h"
//#include "assimp/postprocess.h"
//#include "assimp/cimport.h"

class Importer
{
public:
	Importer();
	~Importer();
	
	void ImportMaterial(const aiMaterial* material, Material* ourMaterial);
	uint64 SaveMaterial(const Material* ourMaterial, char** fileBuffer);
	void LoadMaterial(const char** fileBuffer, Material* ourMaterial);

	uint64 SaveMesh(Mesh mesh);
};