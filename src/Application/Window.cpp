#include "Application/Window.h"
#include "Stopwatch.h"
#include "Rendering/GpuResourceBackend.h"
#include "Rendering/Renderer.h"


IWindow::IWindow(unsigned int width, unsigned int height, bool bFullscreen) :
	size(width, height),
	bFullscreen(bFullscreen)
{}



void IWindow::run()
{
	stopwatch::Stopwatch sw;
	
	float lastTime = sw.elapsed() / 1000.0f;

	// Simple gameloop
	while (!windowShouldClose())
	{
		// Calculate delta time
		float now = (float)sw.elapsed() / 1000.0f;
		float deltaTime = lastTime - now;
		lastTime = now;
		// Update Window
		updateWindow(deltaTime);
		// All Game Updates
		OnFrameUpdateDelegate.broadcast(deltaTime);
		// All GPU Resource updates
		
		// Render actual frame
		GpuResourceBackend::get()->getRenderer()->executeRenderJobs({});

	}
}
