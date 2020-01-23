#pragma once
#include <set>
#include <memory>
#include "Rendering/GpuResourceBackend.h"

class IBackendTexture;
class IBackendIndexedGeometry;
class Renderer;

class GLResourceBackend : public GpuResourceBackend
{
public: 

	GLResourceBackend();


	virtual std::unique_ptr<IBackendTexture> createBackendTexture2D(ITexture* texture)  override;
	
	virtual std::unique_ptr<IBackendIndexedGeometry> createBackendIndexedGeometry(IndexedGeometry* geometry)  override;

	virtual std::unique_ptr<IBackendShader> createBackendShader(Shader * geometry) override;


	virtual Renderer* getRenderer() override;

private: 
	std::shared_ptr<Renderer> renderer;
};