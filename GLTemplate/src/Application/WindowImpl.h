#pragma once

#include "Application/Window.h"
#include "Rendering/GL/OpenGL.h"
#include "Rendering/GL/RenderTaskImpl.h"

#include <string>
#include <string_view>

namespace Rendering
{
class IContext;

namespace GL
{
	class ContextImpl;
}
}


namespace Application
{


class WindowGLFW : public IWindow
{
public:

	std::shared_ptr<WindowGLFW> static create(const glm::uvec2& resolution, std::string_view windowTitle, bool fullscreen, std::shared_ptr<Rendering::GL::ContextImpl> = nullptr);


	std::shared_ptr<Rendering::IContext> getContext() override;


	IDelegate<>& onBeginFrame() override;


	IDelegate<>& onEndFrame() override;

	IDelegate<>& onWindowClosed();


	//IDelegate<glm::uvec2>& onWindowResized();


	//IDelegate<glm::uvec2>& onMouseMoved();




	glm::uvec2 getSize() const;


	void setSize(const glm::uvec2& size);


	const std::string& getTitle() const;


	void setTitle(std::string_view title);


	bool isFullscreen() const;


	void setFullscreen(bool fullscreen);


	void close();
	

	void newFrame(double elapsedInSeconds);


	void enqueueRenderTask(Rendering::IRenderTask::Ptr renderTask) override;

private:

	void enqueueRenderTask_Impl(Rendering::GL::RenderTaskImpl::Ptr renderTask);

	/*void onKeyPressed(const Application::InputChord& chord);


	void onMouseMoved(uint32_t posX, uint32_t posY);


	void onMouseButtonPressed(const Application::InputChord& chord);


	void onTextEntered(uint32_t unicode);*/


	//DelegateImpl<glm::uvec2> mOnWindowResizedDelegate;


	//DelegateImpl<glm::uvec2> mOnMouseMovedDelegate;


	DelegateImpl<> mOnBeginFrameDelegate;

	DelegateImpl<> mOnEndFrameDelegate;

	DelegateImpl<> mOnWindowClosedDelegate;


	std::shared_ptr<GLFWwindow> mWindowHandle{ nullptr };


	std::shared_ptr<Rendering::IContext> mRenderingContext;


	std::string mTitle;


	bool mIsFullscreen;


	struct
	{
		glm::uvec2 postion;
		glm::uvec2 size;
	} mWindowedMode;


	struct
	{
		glm::uvec2 postion;
		glm::uvec2 size;
	} mFullscreenMode;


	std::vector<Rendering::GL::RenderTaskImpl::Ptr> mRenderTasks;

};

}