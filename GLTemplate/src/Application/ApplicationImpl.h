#pragma once

#include "Application/Application.h"
#include "Application/WindowImpl.h"
#include <vector>


namespace Application
{


class ApplicationImpl : public Application
{
public:

	ApplicationImpl(Rendering::GraphicsAPI);


	~ApplicationImpl();


	std::shared_ptr<IWindow> createWindow(const glm::uvec2 & resolution, std::string_view title, bool fullscreen) override;


	Rendering::GraphicsAPI getGraphicsAPI() const  override;


	void run() override;


	void stop() override;


private:

	void mainLoop();

	Rendering::GraphicsAPI mGraphicsAPI;

	std::vector<std::weak_ptr<WindowGLFW>> mRegisteredWindows;

	std::atomic<bool> mStopApplication{ false };

	std::atomic<bool> mIsRunning{ false };
};

}