#include "Importer.h"

Importer::Importer()
{
}

Importer::~Importer()
{
}

void Importer::ImportMaterial(const aiMaterial* material, Material* ourMaterial)
{

}

uint64 Importer::SaveMaterial(const Material* ourMaterial, char** fileBuffer)
{
	return uint64();
}

void Importer::LoadMaterial(const char** fileBuffer, Material* ourMaterial)
{
}
