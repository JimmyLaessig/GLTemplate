#pragma once
#include "Rendering/internal/BaseObject.h"

#include "Base/Enum.h"


namespace Rendering
{
class IRenderObject;
class IFramebufferObject;


ENUM_CLASS(ClearOp,
	ON_BIND,
	NEVER);


class GLTEMPLATE_API IRenderTask : public Rendering::BaseObject
{
public: 

	struct Config
	{
		std::vector< std::shared_ptr<IRenderObject>> mRenderObjects;
		std::shared_ptr<IFramebufferObject> mFrameBuffer;
		ClearOp mClearOp{ ClearOp::NEVER };
	};
	
	using Rendering::BaseObject::BaseObject;
	using Ptr = std::shared_ptr<IRenderTask>;
	

	virtual void execute() = 0;
};
}