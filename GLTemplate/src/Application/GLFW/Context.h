//#pragma once
//
//#include "Base/NonCopyable.h"
//
//#include "Rendering/GL/OpenGL.h"
////#include "Application/Input.h"
//#include <memory>
//#include <functional>
//#include <map>
//#include <tuple>
//
//namespace Application
//{
//namespace GLFW
//{
//
//struct WindowConfig
//{
//	uint32_t width{1920};
//	uint32_t height{1080};
//	std::string title{"\\oo/"};
//	bool fullscreen{false};
//
//	GLFWwindow* shared{nullptr};
//
//	/*std::function<void(const Application::InputChord&)> keyCallback;
//	std::function<void(const Application::InputChord&)> mouseButtonCallback;
//	std::function<void(uint32_t, uint32_t)> cursorPosCallback;
//	std::function<void(uint32_t)> textCallback;*/
//};
//
//
////std::unordered_map<Application::Key, int> KeyLookup;
//
//
//class Context : Base::NonCopyable
//{
//private: 
//
//	Context() = default;
//
//public: 
//
//	~Context();
//
//
//	static std::shared_ptr<Context> Instance();
//
//
//	std::shared_ptr<GLFWwindow> createWindow(const WindowConfig& config);
//
//
//	/*static void nativeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
//
//
//	static void nativeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
//
//
//	static void nativeCursorPosCallback(GLFWwindow* window, double posX, double posY);
//
//
//	static void nativeTextCallback(GLFWwindow* window, unsigned int codepoint);*/
//
//private:
//
//	//std::unordered_map<GLFWwindow*, WindowConfig> mRegisteredWindows;
//
//};
//}
//}