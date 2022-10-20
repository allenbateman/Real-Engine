#include "Scene.h"

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


bool Scene::Awake()
{
	return true;
}

bool Scene::Start()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return true;
}

bool Scene::PreUpdate()
{
	return true;
}

bool Scene::Update(float dt)
{
	return true;
}

bool Scene::PostUpdate()
{
	return true;
}

bool Scene::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}

bool Scene::HandleEvent(Event* singleEvent)
{
	return true;
}

GameObject* Scene::CreateGameObject()
{
	return nullptr;
}
void Scene::LoadFile()
{
	std::cout << "Hola" << endl;
	//const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	const char* file_path ="C:/Users/fernandofg2/Desktop/GitHub/Real-Engine/Real Engine/Output/Assets/BakerHouse.fbx" ;
	//file_path.Create("C:/Users/fernandofg2/Desktop/GitHub/Real-Engine/Real Engine/Output/Assets/BakerHouse.fbx");
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene -> HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
	}
	else
	{
		std::cout << "Error loading scene"<< file_path << endl;
	}
		
	
	// copy vertices
	//ourMesh.num_vertices = aiMesh->mNumVertices;
	//ourMesh.vertices = new float[ourMesh.num_vertices * 3];
	//memcpy(ourMesh.vertices, aiMesh->mVertices, sizeof(float) * ourMesh.num_vertices * 3);
	////LOG("New mesh with %d vertices", m.num_vertices);

	// // copy faces
	//if (aiMesh->HasFaces())
	//{
	//	ourMesh.num_indices = aiMesh->mNumFaces * 3;
	//	ourMesh.indices = new uint[m.num_indices]; // assume each face is a triangle
	//	for (uint i = 0; i < aiMesh->mNumFaces; ++i)
	//	{
	//		if (aiMesh->mFaces[i].mNumIndices != 3)
	//			LOG("WARNING, geometry face with != 3 indices!");
	//		else
	//			memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
	//	}
	//}
	
}
