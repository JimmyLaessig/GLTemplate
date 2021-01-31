#pragma once
#include "Rendering/internal/BaseObject.h"

#include "Base/Enum.h"

#include <memory>
#include <unordered_map>

namespace Rendering
{
class IPipelineState;
class IBuffer;
class IShaderProgram;
class IUniformCollection;
class IIndexedMesh;




class GLTEMPLATE_API IRenderObject : public Rendering::BaseObject
{
public: 

	using Rendering::BaseObject::BaseObject;

	using Ptr = std::shared_ptr<IRenderObject>;

	struct Config
	{
		std::shared_ptr<IIndexedMesh> mesh;
		std::shared_ptr<IShaderProgram> shader;
		std::shared_ptr<IUniformCollection> uniforms;

		std::shared_ptr<IPipelineState> pipelineState;

		uint32_t renderPass{0};
	};
};
}