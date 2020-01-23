#include "Components/IndexedGeometry.h"
#include "Rendering/GpuResourceBackend.h"
#include <algorithm>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <Stopwatch.h>
#include <optional>



IndexedGeometry::IndexedGeometry(const IndexedGeometryData& vertexData, Material* material, const std::string_view name) :
	name(name),
	vertexData(vertexData),
	material(material),
	backendIndexedGeometry(GpuResourceBackend::get()->createBackendIndexedGeometry(this))
{}


IndexedGeometry::IndexedGeometry(IndexedGeometryData&& vertexData, Material* material, const std::string_view name) :
	name(name),
	vertexData(std::move(vertexData)),
	material(material),
	backendIndexedGeometry(GpuResourceBackend::get()->createBackendIndexedGeometry(this))
{}



void IndexedGeometry::setMaterial(Material * material)
{	
	this->material = material;
}


const IndexedGeometryData & IndexedGeometry::getVertexData() const
{
	return this->vertexData;
}


Material * IndexedGeometry::getMaterial()
{
	return material;
}