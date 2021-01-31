#pragma once
#include "Rendering/internal/BaseObject.h"
#include "Rendering/Types/AttributeFormat.h"
#include <string>
#include <optional>
#include <memory>

namespace Rendering
{

class IUniformCollection;


class GLTEMPLATE_API IShaderProgram : public Rendering::BaseObject
{
public:

	struct Config
	{
		std::string vertex;
		std::string fragment;
		std::optional<std::string> tessellationControl;
		std::optional<std::string> tessellationEval;
		std::optional<std::string> geometry;
	};


	using Rendering::BaseObject::BaseObject;
	using Ptr = std::shared_ptr<IShaderProgram>;


	virtual void* getNativeHandle() = 0;


	virtual std::shared_ptr<Rendering::IUniformCollection> getGlobalUniformCollection() = 0;


	virtual const std::vector<AttributeSemantic>& getAttributeSemantics() const = 0;
};
}
