#include "Application/Application.h"
#include "Application/ApplicationImpl.h"


namespace Application
{
	std::shared_ptr<Application>
	Application::create(Rendering::GraphicsAPI graphicsAPI)
	{
		return std::shared_ptr<Application>(new ApplicationImpl(graphicsAPI));
	}
}