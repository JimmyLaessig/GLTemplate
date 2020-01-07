#pragma once
#include <set>
#include <functional>
#include "Transform.h"
#include "GLSLShader.h"

struct RenderObject
{
	RenderObject() = delete;

	RenderObject(DrawableGpuResource* drawable, Transform transform, GLSLShader* shader, UniformCollection* uniforms, int renderPass);

	RenderObject(const RenderObject& other);

	RenderObject(RenderObject&& other);

	/**
	 * The actual draw command to render the object.
	 */
	DrawableGpuResource* drawable;

	/**
	 * The transform of the object.
	 */
	Transform transform;

	/**
	 * The shader of the object
	 */
	GLSLShader* shader;

	/**
	 * The object-specific uniforms for the shader. (Does not include view-specific uniforms)
	 */
	UniformCollection* uniforms;

	/**
	 * The lower the number the earlier this primitive is rendered.
	 */
	int renderPass;

};

/**
 * The IRenderable class describes objects that can be drawn by the Renderer by submitting an RenderObject
 */
class IRenderJob
{
public: 

	/**
	 * Constructs a new IRenderable and registeres it with the active Renderer.
	 */
	IRenderJob();

	/**
	 * Desctruct ab IRenderable and unregisteres it with the active Renderer.
	 */
	virtual ~IRenderJob();

	/**
	 * Gets the RenderObject of the renderable containing all drawcall infos.
	 */
	virtual std::vector<RenderObject> toRenderObject() = 0;

	/**
	 * Returns whether or not the render job should be executed.
	 */
	virtual bool isActive() const;

	/**
	 * (De-)activat3es the render job.
	 */
	virtual void setActive(bool bActive);

private: 

	bool bisIsActive = true;
};

struct RenderView
{
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

struct RenderObjectCompare
{
	bool operator()(const RenderObject& lhs, const RenderObject& rhs)
	{
		return lhs.renderPass < rhs.renderPass;
	}
};

class Renderer
{
public: 

	virtual void submitOneTimeRenderObject(RenderObject ro);

	/**
	 * Updates the renderer and executes all render jobs for the given frame.
	 */
	virtual void executeRenderJobs(const RenderView& view);

private:

	friend class IRenderJob;

	/**
	 * Submits a RenderObject to the renderer.
	 */
	void registerRenderJob(IRenderJob* renderJob);

	/**
	 * Removes the RenderJob from the renderer.
	 */
	void unregisterRenderJob(IRenderJob* renderJob);

	/**
	 * Holds all registered renderables
	 */
	std::set<class IRenderJob*> renderJobs;

	/**
	 * 
	 */
	std::vector<RenderObject> oneTimeRenderObjects;
};