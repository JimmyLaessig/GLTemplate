#pragma once

//#include "Application/Input.h"
#include "Application/Delegate.h"
#include "Rendering/Context.h"

#include <glm/glm.hpp>

#include <string_view>
#include <memory>

namespace Rendering
{
	//class Framebuffer;
	//class IRenderTask;
}


namespace Application
{

class IWindow
{

public:

	virtual IDelegate<>& onBeginFrame() = 0;


	virtual IDelegate<>& onEndFrame() = 0;


	virtual IDelegate<>& onWindowClosed() = 0;


	virtual std::shared_ptr<Rendering::IContext> getContext() = 0;


	virtual void enqueueRenderTask(Rendering::IRenderTask::Ptr renderTask) = 0;
};
}