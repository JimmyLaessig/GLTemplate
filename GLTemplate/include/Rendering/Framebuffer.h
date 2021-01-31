#pragma once
#include "Rendering/internal/BaseObject.h"

#include "Base/Enum.h"

#include <glm/glm.hpp>

namespace Rendering
{
class ITexture;
class ITexture2D;

struct ColorAttachment
{
	std::shared_ptr<Rendering::ITexture2D> texture;
	glm::vec4 clearColor{0,0,0,1};
};


struct DepthStencilAttachment
{
	std::shared_ptr<Rendering::ITexture2D> texture;
	float clearDepth{1};
	float clearStencil{0};
};


class GLTEMPLATE_API IFramebufferObject : public Rendering::BaseObject
{
public:
	using Rendering::BaseObject::BaseObject;
	using Ptr = std::shared_ptr<IFramebufferObject>;


	struct Config
	{
		std::vector<ColorAttachment> colorAttachments;
		std::optional<DepthStencilAttachment> depthStencilAttachment;
	};


	virtual std::shared_ptr<ITexture2D> getDepthStencilAttachment() = 0;
	 
	 
	virtual std::shared_ptr<ITexture2D> getColorAttachment(size_t index) = 0;
};
} // namespace Rendering
