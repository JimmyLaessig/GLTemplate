#include "Rendering/Renderer.h"
#include "Rendering/GpuResourceBackend.h"
#include <numeric>



IRenderJob::IRenderJob()
{
	if (auto backend = GpuResourceBackend::get())
	{
		if (auto renderer = backend->getRenderer())
		{
			renderer->registerRenderJob(this);
		}
	}
}


IRenderJob::~IRenderJob()
{
	if (auto backend = GpuResourceBackend::get())
	{
		if (auto renderer = backend->getRenderer())
		{
			renderer->unregisterRenderJob(this);
		}
	}
}


bool IRenderJob::isActive() const
{
	return bisIsActive;
}


void IRenderJob::setActive(bool bActive)
{
	this->bisIsActive = bActive;
}


void Renderer::registerRenderJob(IRenderJob * renderJob)
{
	this->renderJobs.insert(renderJob);
}


void Renderer::unregisterRenderJob(IRenderJob * renderJob)
{
	this->renderJobs.erase(renderJob);
}


void Renderer::submitOneTimeRenderObject(RenderObject ro)
{
	oneTimeRenderObjects.push_back(std::move(ro));
}


void Renderer::executeRenderJobs(const RenderView & view)
{
	
	//std::vector<RenderObject> renderObjects;

	//// Compile a sorted set of renderObjects
	//// Discard all inactive RenderJobs
	//// Perform culling operations
	//
	//for (auto renderJob : renderJobs)
	//{
	//	if (!renderJob->isActive())
	//	{
	//		continue;
	//	}
	//	
	//	for (auto& ro : renderJob->toRenderObject())
	//	{
	//		renderObjects.push_back(std::move(ro));
	//	}
	//}

	//// Sort objects by renderPass
	//std::sort(renderObjects.begin(), renderObjects.end(), [](const RenderObject& lhs, const RenderObject& rhs) 
	//{
	//	return lhs.renderPass < rhs.renderPass; 
	//});
	
	// Execute each RenderObject

	for (auto& ro : oneTimeRenderObjects)
	{
		/*if (ro.drawable)
		{
			if (ro.shader)
			{
				ro.shader->bind();
				auto worldMatrix = ro.transform.getLocalToWorldMatrix();
				auto normalMatrix = ro.transform.getLocalToWorldNormalMatrix();

				auto worldViewProjectionMatrix = view.projectionMatrix * view.viewMatrix * worldMatrix;
				glUniformMatrix4fv(glGetUniformLocation(ro.shader->programHandle, "WorldViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(worldViewProjectionMatrix));
			}
			ro.drawable->getDrawCall()();
		}*/
	}
	oneTimeRenderObjects.clear();
	// Execute each RenderObject
	//for (auto& ro : renderObjects)
	//{
//
//	}
}


RenderObject::RenderObject(IndexedGeometry * drawable, Transform transform, Shader * shader, UniformCollection * uniforms, int renderPass):
	geometry(geometry),
	transform(transform),
	shader(shader),
	uniforms(uniforms),
	renderPass(renderPass)
{}