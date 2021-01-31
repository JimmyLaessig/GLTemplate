#include "ApplicationImpl.h"
#include "WindowImpl.h"

#include <memory>

namespace Application
{

ApplicationImpl::ApplicationImpl(Rendering::GraphicsAPI api) :
	mGraphicsAPI(api)
{
	static std::mutex mutex;
	static bool initialized = false;
	std::scoped_lock lock(mutex);
	
	// Only one GLFW application allowed
	assert(initialized == false);

	// GLFW must be initialized
	assert(glfwInit() == GLFW_TRUE);

	// Create a debug OpenGL context or tell your OpenGL library (GLFW, SDL) to do so.
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Set window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_REFRESH_RATE, 60);
	initialized = true;
}


ApplicationImpl::~ApplicationImpl()
{
	glfwTerminate();
}


std::shared_ptr<IWindow> 
ApplicationImpl::createWindow(const glm::uvec2& resolution, std::string_view title, bool fullscreen)
{
	if (auto win = WindowGLFW::create(resolution, title, fullscreen, nullptr))
	{ 
		mRegisteredWindows.emplace_back(win);

		return win;
	}
	return nullptr;
}


Rendering::GraphicsAPI 
ApplicationImpl::getGraphicsAPI() const
{
	return mGraphicsAPI;
}


void 
ApplicationImpl::run()
{
	// Run the main loop
	// The main loop is protected against recursive calls to run()
	bool expected = false;
	if (mIsRunning.compare_exchange_strong(expected, true))
	{
		mainLoop();
		mIsRunning.store(false);
	}
	else
	{
		assert(false && "Do not call run() if the application is already running.");
	}
}


void 
ApplicationImpl::stop()
{
	bool expected = true;
	if (!mIsRunning.compare_exchange_strong(expected, false))
	{
		// TODO LOG that application is not running
	}
}


void
ApplicationImpl::mainLoop()
{
	// Convinience lambda
	auto getElapsed = [prev = glfwGetTime()]() mutable
	{
		auto now = glfwGetTime();
		auto delta = now - prev;
		prev = now;
		return delta;
	};

	// Application main loop
	while (mIsRunning.load())
	{
		auto elapsed = getElapsed();
		// Execute each windows' onNewFrame function
		for (auto win : mRegisteredWindows)
		{
			if (auto ptr = win.lock())
			{
				
				ptr->newFrame(elapsed);
			}
			else
			{
				//mRegisteredWindows.erase(win);
			}
		}

		glfwPollEvents();
	}
}

}