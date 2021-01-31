#pragma once

#include "Application/Window.h"
#include "Rendering/Context.h"

#include <glm/glm.hpp>

#include <string_view>
#include <memory>


namespace Application
{

class Application
{

public:

	virtual ~Application() = default;


	static std::shared_ptr<Application> create(Rendering::GraphicsAPI graphicsAPI);


	virtual std::shared_ptr<IWindow> createWindow(const glm::uvec2& resolution, std::string_view title, bool fullscreen) = 0;


	virtual Rendering::GraphicsAPI getGraphicsAPI() const = 0;
	
	
	virtual void run() = 0;


	virtual void stop() = 0;

protected: 

};
}