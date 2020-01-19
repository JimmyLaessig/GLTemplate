#include "Rendering/Mesh.h"
#include <algorithm>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <Stopwatch.h>
#include <optional>



IndexedGeometryData::IndexedGeometryData(const IndexedGeometryData & other) :
	positions(other.positions),
	normals(other.normals),
	tangents(other.tangents),
	bitangents(other.bitangents),
	colors(other.colors),
	uvs(other.uvs),
	indices(other.indices)
{}


IndexedGeometryData::IndexedGeometryData(IndexedGeometryData && other) :
	positions(std::move(other.positions)),
	normals(std::move(other.normals)),
	tangents(std::move(other.tangents)),
	bitangents(std::move(other.bitangents)),
	colors(std::move(other.colors)),
	uvs(std::move(other.uvs)),
	indices(std::move(other.indices))
{}


IndexedGeometryData & IndexedGeometryData::operator=(const IndexedGeometryData & other)
{
	this->positions		= other.positions;
	this->normals		= other.normals;
	this->tangents		= other.tangents;
	this->bitangents	= other.bitangents;
	this->colors		= other.colors;
	this->uvs			= other.uvs;
	this->indices		= other.indices;

	return *this;
}


IndexedGeometryData & IndexedGeometryData::operator=(IndexedGeometryData && other)
{
	this->positions		= std::move(other.positions);
	this->normals		= std::move(other.normals);
	this->tangents		= std::move(other.tangents);
	this->bitangents	= std::move(other.bitangents);
	this->colors		= std::move(other.colors);
	this->uvs			= std::move(other.uvs);
	this->indices		= std::move(other.indices);

	return *this;
}


IndexedGeometry::IndexedGeometry(const IndexedGeometryData& vertexData, Material* material) :
	vertexData(vertexData),
	material(material)
{
	markOutdated();
}


IndexedGeometry::IndexedGeometry(IndexedGeometryData&& vertexData, Material* material) :
	vertexData(std::move(vertexData)),
	material(material)
{
	markOutdated();
}



IndexedGeometry::~IndexedGeometry()
{
	freeGpuMemory();
}


void IndexedGeometry::setMaterial(Material * material)
{
	getResourceLock().lock();
	this->material = material;
	getResourceLock().unlock();
}


const IndexedGeometryData & IndexedGeometry::getVertexData() const
{
	return this->vertexData;
}


Material * IndexedGeometry::getMaterial()
{
	return material;
}