#include "WindowImpl.h"

#include "Rendering/GL/ContextImpl.h"
#include "Rendering/GL/BufferImpl.h"
#include "Rendering/GL/ShaderImpl.h"
#include "Rendering/GL/UniformCollectionImpl.h"
#include "Rendering/GL/RenderObjectImpl.h"

#include "GLFW/Context.h"

#include <functional>
#include <iostream>
#include <unordered_map>
#include <mutex>
#include <array>

#include "Rendering/Util.h"

namespace Application
{

std::shared_ptr<WindowGLFW>
WindowGLFW::create(const glm::uvec2& resolution, std::string_view windowTitle, bool fullscreen, std::shared_ptr<Rendering::GL::ContextImpl> sharedContext)
{
	// Make sure that GLFW is initialized
	/*auto glfwContext = GLFW::Context::Instance();
	if (!glfwContext)
	{
		return nullptr;
	}*/

	GLFWwindow* sharedContextWindow = sharedContext ? sharedContext->getNativeWindowHandle() : nullptr;


	std::shared_ptr<WindowGLFW> window(new WindowGLFW);

	
	// Create a GLFW window

	//GLFW::WindowConfig conf;
	//{
	//	conf.width					= resolution.x;
	//	conf.height					= resolution.y;
	//	conf.title					= std::string(windowTitle);
	//	conf.fullscreen				= fullscreen;
	//	conf.shared					= sharedContextWindow;
	//	conf.keyCallback			= std::bind(&WindowGLFW::onKeyPressed, window.get(), std::placeholders::_1);
	//	conf.mouseButtonCallback	= std::bind(&WindowGLFW::onMouseButtonPressed, window.get(), std::placeholders::_1);
	//	conf.cursorPosCallback		= std::bind(&WindowGLFW::onMouseMoved, window.get(), std::placeholders::_1, std::placeholders::_2);
	//	conf.textCallback			= std::bind(&WindowGLFW::onTextEntered, window.get(), std::placeholders::_1);
	//};

	std::string title(windowTitle.data(), windowTitle.size());

	window->mWindowHandle.reset(glfwCreateWindow(resolution.x, 
												 resolution.y, 
												 title.c_str(),
												 nullptr, 
												 sharedContext ? sharedContext->getNativeWindowHandle() : nullptr
								), 
								// Override deleter to provide glfw call
								[](auto win) {glfwDestroyWindow(win); });


	//  Make sure that GLFW was able to create a windows
	if (!window->mWindowHandle)
	{
		return nullptr;
	}

	// If no shared context is passed, create a new one
	window->mRenderingContext = sharedContext ? sharedContext : Rendering::GL::ContextImpl::create(window->mWindowHandle);


	// Make sure that a Context exists
	if (!window->mRenderingContext)
	{
		return nullptr;
	}

	return window;
}


std::shared_ptr<Rendering::IContext>
WindowGLFW::getContext()
{
	return std::static_pointer_cast<Rendering::IContext>(mRenderingContext);
}


//void 
//WindowGLFW::onKeyPressed(const InputChord& chord)
//{
//
//}
//
//
//void 
//WindowGLFW::onMouseMoved(uint32_t posX, uint32_t posY)
//{
//
//}
//
//
//void 
//WindowGLFW::onMouseButtonPressed(const InputChord& chord)
//{
//
//}
//
//
//void 
//WindowGLFW::onTextEntered(uint32_t unicode)
//{
//
//}


IDelegate<>& 
WindowGLFW::onBeginFrame()
{
	return mOnBeginFrameDelegate;
}


IDelegate<>&
WindowGLFW::onEndFrame()
{
	return mOnEndFrameDelegate;
}


//IDelegate<glm::uvec2>& 
//WindowGLFW::onWindowResized()
//{
//	return mOnWindowResizedDelegate;
//}
//
//
//IDelegate<glm::uvec2>& 
//WindowGLFW::onMouseMoved()
//{
//	return mOnMouseMovedDelegate;
//}


IDelegate<>& 
WindowGLFW::onWindowClosed()
{
	return mOnWindowClosedDelegate;
}


glm::uvec2 
WindowGLFW::getSize() const
{
	return mIsFullscreen ? mFullscreenMode.size : mWindowedMode.size;
}


void 
WindowGLFW::setSize(const glm::uvec2& size)
{
	glfwSetWindowSize(mWindowHandle.get(), size.x, size.y);
	int x, y;
	glfwGetWindowSize(mWindowHandle.get(), &x, &y);


	if (mIsFullscreen)
	{
		mFullscreenMode.size = glm::uvec2(x, y);
	}
	else
	{
		mWindowedMode.size = glm::uvec2(x, y);
	}
}


const std::string&
WindowGLFW::getTitle() const
{
	return mTitle;
}


void 
WindowGLFW::setTitle(std::string_view title)
{
	mTitle = std::string(title.data(), title.size());
	glfwSetWindowTitle(mWindowHandle.get(), mTitle.c_str());
}


bool 
WindowGLFW::isFullscreen() const
{
	return mIsFullscreen;
}


void 
WindowGLFW::setFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		int px, py;
		glfwGetWindowPos(mWindowHandle.get(), &px, &py);
		mWindowedMode.postion = { px, py };

		// get resolution of monitor
		auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			
		// switch to full screen
		glfwSetWindowMonitor(mWindowHandle.get(), glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);

		mFullscreenMode.postion = { 0, 0 };
		mFullscreenMode.size	= { mode->width, mode->height };
	}
	else
	{
		// restore last window size and position
		glfwSetWindowMonitor(mWindowHandle.get(), nullptr, mWindowedMode.postion.x, mWindowedMode.postion.y, mWindowedMode.size.x, mWindowedMode.size.y, 0);
	}

	mIsFullscreen = fullscreen;
}


void 
WindowGLFW::close()
{

	glfwSetWindowShouldClose(mWindowHandle.get(), GLFW_TRUE);

	// Execute the callbacks after the run method has finished
	mOnWindowClosedDelegate.broadcast();

}


void
WindowGLFW::newFrame(double elapsedInSeconds)
{
	glfwMakeContextCurrent(mWindowHandle.get());
	//glfwWindowShouldClose(mWindowHandle.get()) == GLFW_TRUE);
	mOnBeginFrameDelegate.broadcast();

	for (auto task : mRenderTasks)
	{
		task->execute();
	}

	mOnEndFrameDelegate.broadcast();

	// At the end of a frame, swap the buffer to actually present the image
	glfwSwapBuffers(mWindowHandle.get());
}


void 
WindowGLFW::enqueueRenderTask(Rendering::IRenderTask::Ptr renderTask)
{
	if (renderTask->getContext() == getContext())
	{
		enqueueRenderTask_Impl(std::static_pointer_cast<Rendering::GL::RenderTaskImpl>(renderTask));
	}
}



void
WindowGLFW::enqueueRenderTask_Impl(Rendering::GL::RenderTaskImpl::Ptr renderTask)
{
	// TODO 
	mRenderTasks.push_back(renderTask);
}


}