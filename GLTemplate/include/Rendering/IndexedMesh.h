#pragma once

#include "Rendering/internal/BaseObject.h"
#include "Rendering/Types/AttributeFormat.h"
#include "Base/Enum.h"


#include <unordered_map>
#include <optional>


namespace Rendering
{
class IBuffer;


ENUM_CLASS(PrimitiveType,
	POINTS,
	LINES,
	LINE_STRIP,
	LINE_LOOP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN
);


class GLTEMPLATE_API IIndexedMesh : public Rendering::BaseObject
{
public:
	using Rendering::BaseObject::BaseObject;
	using Ptr = std::shared_ptr<IIndexedMesh>;


	struct Config
	{
		PrimitiveType primitiveType{ PrimitiveType::TRIANGLES };

		std::shared_ptr<IBuffer> indexBuffer;
		std::unordered_map<std::string, std::shared_ptr<IBuffer>> vertexBuffers;
	};
};
}
