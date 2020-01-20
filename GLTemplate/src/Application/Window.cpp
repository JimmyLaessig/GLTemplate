#include "Application/Window.h"
#include "Stopwatch.h"
#include "Rendering/GpuResourceBackend.h"
#include "Rendering/Renderer.h"
#include "imgui.h"

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
		float now = (float)sw.elapsed<stopwatch::Stopwatch::MICROSECONDS>() * 1e-6f;
		float deltaTime = now - lastTime;
		lastTime = now;
		// Update Window
		prepareUpdate(deltaTime);


		if (imGuiWrapper){imGuiWrapper->NewFrame();}

		// All Game Updates
		OnFrameUpdateDelegate.broadcast(deltaTime);
		
		prepareRender();
		// All GPU Resource updates
		GpuResourceBackend::get()->update(deltaTime);

		// Render actual frame
		GpuResourceBackend::get()->getRenderer()->executeRenderJobs({});

		// Finally, Draw UI
		if(imGuiWrapper){imGuiWrapper->Render();}

		finishRender();
	}
}
