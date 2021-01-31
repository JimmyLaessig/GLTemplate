//#pragma once
//#include "Application/GLFW/Context.h"
////#include "Application/Input.h"
//#include <unordered_map>
//
//namespace Application
//{
//namespace GLFW
//{
//	/*std::unordered_map<Application::Key, int> KeyLookup =
//	{
//		{ Key::SPACE 		, GLFW_KEY_SPACE 		},
//		{ Key::APOSTROPHE	, GLFW_KEY_APOSTROPHE	},
//		{ Key::COMMA		, GLFW_KEY_COMMA		},
//		{ Key::MINUS 		, GLFW_KEY_MINUS 		},
//		{ Key::PERIOD		, GLFW_KEY_PERIOD		},
//		{ Key::SLASH 		, GLFW_KEY_SLASH 		},
//		{ Key::ZERO 		, GLFW_KEY_0 			},
//		{ Key::ONE 			, GLFW_KEY_1 			},
//		{ Key::TWO 			, GLFW_KEY_2 			},
//		{ Key::THREE 		, GLFW_KEY_3 			},
//		{ Key::FOUR 		, GLFW_KEY_4 			},
//		{ Key::FIVE 		, GLFW_KEY_5 			},
//		{ Key::SIX 			, GLFW_KEY_6 			},
//		{ Key::SEVEN 		, GLFW_KEY_7 			},
//		{ Key::EIGHT 		, GLFW_KEY_8 			},
//		{ Key::NINE 		, GLFW_KEY_9 			},
//		{ Key::SEMICOLON	, GLFW_KEY_SEMICOLON	},
//		{ Key::EQUAL 		, GLFW_KEY_EQUAL 		},
//		{ Key::A 			, GLFW_KEY_A 			},
//		{ Key::B			, GLFW_KEY_B			},
//		{ Key::C 			, GLFW_KEY_C 			},
//		{ Key::D 			, GLFW_KEY_D 			},
//		{ Key::E 			, GLFW_KEY_E 			},
//		{ Key::F 			, GLFW_KEY_F 			},
//		{ Key::G 			, GLFW_KEY_G 			},
//		{ Key::H 			, GLFW_KEY_H 			},
//		{ Key::I 			, GLFW_KEY_I 			},
//		{ Key::J 			, GLFW_KEY_J 			},
//		{ Key::K 			, GLFW_KEY_K 			},
//		{ Key::L 			, GLFW_KEY_L 			},
//		{ Key::M 			, GLFW_KEY_M 			},
//		{ Key::N 			, GLFW_KEY_N 			},
//		{ Key::O 			, GLFW_KEY_O 			},
//		{ Key::P 			, GLFW_KEY_P 			},
//		{ Key::Q 			, GLFW_KEY_Q 			},
//		{ Key::R 			, GLFW_KEY_R 			},
//		{ Key::S 			, GLFW_KEY_S 			},
//		{ Key::T 			, GLFW_KEY_T 			},
//		{ Key::U 			, GLFW_KEY_U 			},
//		{ Key::V 			, GLFW_KEY_V 			},
//		{ Key::W 			, GLFW_KEY_W 			},
//		{ Key::X 			, GLFW_KEY_X 			},
//		{ Key::Y 			, GLFW_KEY_Y 			},
//		{ Key::Z 			, GLFW_KEY_Z 			},
//		{ Key::LEFT_BRACKET , GLFW_KEY_LEFT_BRACKET },
//		{ Key::BACKSLASH	, GLFW_KEY_BACKSLASH	},
//		{ Key::RIGHT_BRACKET, GLFW_KEY_RIGHT_BRACKET},
//		{ Key::GRAVE_ACCENT	, GLFW_KEY_GRAVE_ACCENT	},
//		{ Key::WORLD_1		, GLFW_KEY_WORLD_1		},
//		{ Key::WORLD_2		, GLFW_KEY_WORLD_2		},
//		{ Key::ESCAPE 		, GLFW_KEY_ESCAPE 		},
//		{ Key::ENTER 		, GLFW_KEY_ENTER 		},
//		{ Key::TAB 			, GLFW_KEY_TAB 			},
//		{ Key::BACKSPACE	, GLFW_KEY_BACKSPACE	},
//		{ Key::INSERT 		, GLFW_KEY_INSERT 		},
//		{ Key::DELETE 		, GLFW_KEY_DELETE 		},
//		{ Key::RIGHT 		, GLFW_KEY_RIGHT 		},
//		{ Key::LEFT 		, GLFW_KEY_LEFT 		},
//		{ Key::DOWN			, GLFW_KEY_DOWN			},
//		{ Key::UP 			, GLFW_KEY_UP 			},
//		{ Key::PAGE_UP 		, GLFW_KEY_PAGE_UP 		},
//		{ Key::PAGE_DOWN 	, GLFW_KEY_PAGE_DOWN 	},
//		{ Key::HOME 		, GLFW_KEY_HOME 		},
//		{ Key::END 		 	, GLFW_KEY_END 		 	},
//		{ Key::CAPS_LOCK	, GLFW_KEY_CAPS_LOCK	},
//		{ Key::SCROLL_LOCK	, GLFW_KEY_SCROLL_LOCK	},
//		{ Key::NUM_LOCK 	, GLFW_KEY_NUM_LOCK 	},
//		{ Key::PRINT_SCREEN	, GLFW_KEY_PRINT_SCREEN	},
//		{ Key::PAUSE 		, GLFW_KEY_PAUSE 		},
//		{ Key::F1 			, GLFW_KEY_F1 			},
//		{ Key::F2 			, GLFW_KEY_F2 			},
//		{ Key::F3 			, GLFW_KEY_F3 			},
//		{ Key::F4 			, GLFW_KEY_F4 			},
//		{ Key::F5 			, GLFW_KEY_F5 			},
//		{ Key::F6 			, GLFW_KEY_F6 			},
//		{ Key::F7 			, GLFW_KEY_F7 			},
//		{ Key::F8 			, GLFW_KEY_F8 			},
//		{ Key::F9 			, GLFW_KEY_F9 			},
//		{ Key::F10 			, GLFW_KEY_F10 			},
//		{ Key::F11 			, GLFW_KEY_F11 			},
//		{ Key::F12 			, GLFW_KEY_F12 			},
//		{ Key::F13 			, GLFW_KEY_F13 			},
//		{ Key::F14 			, GLFW_KEY_F14 			},
//		{ Key::F15 			, GLFW_KEY_F15 			},
//		{ Key::F16 			, GLFW_KEY_F16 			},
//		{ Key::F17 			, GLFW_KEY_F17 			},
//		{ Key::F18 			, GLFW_KEY_F18 			},
//		{ Key::F19 			, GLFW_KEY_F19 			},
//		{ Key::F20 			, GLFW_KEY_F20 			},
//		{ Key::F21 			, GLFW_KEY_F21 			},
//		{ Key::F22 			, GLFW_KEY_F22 			},
//		{ Key::F23 			, GLFW_KEY_F23 			},
//		{ Key::F24 			, GLFW_KEY_F24 			},
//		{ Key::F25 			, GLFW_KEY_F25 			},
//		{ Key::KP_0 		, GLFW_KEY_KP_0 		},
//		{ Key::KP_1 		, GLFW_KEY_KP_1 		},
//		{ Key::KP_2 		, GLFW_KEY_KP_2 		},
//		{ Key::KP_3 		, GLFW_KEY_KP_3 		},
//		{ Key::KP_4 		, GLFW_KEY_KP_4 		},
//		{ Key::KP_5 		, GLFW_KEY_KP_5 		},
//		{ Key::KP_6 		, GLFW_KEY_KP_6 		},
//		{ Key::KP_7 		, GLFW_KEY_KP_7 		},
//		{ Key::KP_8 		, GLFW_KEY_KP_8 		},
//		{ Key::KP_9 		, GLFW_KEY_KP_9 		},
//		{ Key::KP_DECIMAL 	, GLFW_KEY_KP_DECIMAL 	},
//		{ Key::KP_DIVIDE 	, GLFW_KEY_KP_DIVIDE 	},
//		{ Key::KP_MULTIPLY 	, GLFW_KEY_KP_MULTIPLY 	},
//		{ Key::KP_SUBTRACT 	, GLFW_KEY_KP_SUBTRACT 	},
//		{ Key::KP_ADD 		, GLFW_KEY_KP_ADD 		},
//		{ Key::KP_ENTER 	, GLFW_KEY_KP_ENTER 	},
//		{ Key::KP_EQUAL 	, GLFW_KEY_KP_EQUAL 	},
//		{ Key::LEFT_SHIFT 	, GLFW_KEY_LEFT_SHIFT 	},
//		{ Key::LEFT_CONTROL	, GLFW_KEY_LEFT_CONTROL	},
//		{ Key::LEFT_ALT		, GLFW_KEY_LEFT_ALT		},
//		{ Key::LEFT_SUPER 	, GLFW_KEY_LEFT_SUPER 	},
//		{ Key::RIGHT_SHIFT  , GLFW_KEY_RIGHT_SHIFT	},
//		{ Key::RIGHT_CONTROL, GLFW_KEY_RIGHT_CONTROL},
//		{ Key::RIGHT_ALT 	, GLFW_KEY_RIGHT_ALT 	},
//		{ Key::RIGHT_SUPER 	, GLFW_KEY_RIGHT_SUPER	},
//		{ Key::MENU			, GLFW_KEY_MENU			},
//		{ Key::UNKNOWN		, GLFW_KEY_UNKNOWN		},
//	};
//
//
//	std::unordered_map<int, Application::MouseButton> MouseButtonLookup =
//	{
//		{GLFW_MOUSE_BUTTON_1, MouseButton::BUTTON_1},
//		{GLFW_MOUSE_BUTTON_2, MouseButton::BUTTON_2},
//		{GLFW_MOUSE_BUTTON_3, MouseButton::BUTTON_3},
//		{GLFW_MOUSE_BUTTON_4, MouseButton::BUTTON_4},
//		{GLFW_MOUSE_BUTTON_5, MouseButton::BUTTON_5},
//		{GLFW_MOUSE_BUTTON_6, MouseButton::BUTTON_6},
//		{GLFW_MOUSE_BUTTON_7, MouseButton::BUTTON_7},
//		{GLFW_MOUSE_BUTTON_8, MouseButton::BUTTON_8}
//	};
//
//
//	std::unordered_map<int, Application::KeyState> KeyStateLookup =
//	{
//		{GLFW_PRESS, KeyState::PRESSED},
//		{GLFW_REPEAT, KeyState::RELEASED},
//		{GLFW_RELEASE, KeyState::REPEAT},
//	};*/
//
//
//
////	Context::~Context()
////	{
////		glfwTerminate();
////	}
////
////
////	std::shared_ptr<Context> 
////	Context::Instance()
////	{
////		static std::shared_ptr<Context> mInstance;
////
////		if (!mInstance)
////		{
////			if (glfwInit() == GLFW_TRUE)
////			{
////#if _DEBUG
////				// Create a debug OpenGL context or tell your OpenGL library (GLFW, SDL) to do so.
////				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
////#endif
////
////				// Set window hints
////				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
////				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
////				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
////				glfwWindowHint(GLFW_REFRESH_RATE, 60);
////
////				mInstance.reset(new Context);
////			}
////		}
////
////		return mInstance;
////	}
//
//
//	//std::shared_ptr<GLFWwindow>
//	//Context::createWindow(const WindowConfig& config)
//	//{
//	//	auto window = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, config.shared);
//
//	//	// TODO set fullscreen etc.
//
//	//	glfwSetKeyCallback(window, nativeKeyCallback);
//	//	glfwSetMouseButtonCallback(window, nativeMouseButtonCallback);
//	//	glfwSetCursorPosCallback(window, nativeCursorPosCallback);
//	//	glfwSetCharCallback(window, nativeTextCallback);
//	//	
//	//	auto deleter = [](auto* win)
//	//	{
//	//		if (win)
//	//		{
//	//			auto ctx = Context::Instance();
//
//	//			auto itr = ctx->mRegisteredWindows.find(win);
//
//	//			if (itr != ctx->mRegisteredWindows.end())
//	//			{
//	//				ctx->mRegisteredWindows.erase(itr);
//	//			}
//	//			glfwDestroyWindow(win);
//	//		}
//	//	};
//	//	std::shared_ptr<GLFWwindow> windowPtr(window, deleter);
//	//	
//	//	mRegisteredWindows.emplace(windowPtr.get(), config);
//	//	return windowPtr;
//	//}
//
//
//	//void 
//	//Context::nativeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
//	//{
//	//	auto ctx = Context::Instance();
//	//	auto itr = ctx->mRegisteredWindows.find(window);
//	//	if (itr != ctx->mRegisteredWindows.end())
//	//	{
//	//		if (itr->second.keyCallback)
//	//		{
//	//			InputChord chord
//	//			{
//	//				KeyLookup[key],
//	//				KeyStateLookup[action],
//	//				(mods & GLFW_MOD_SHIFT) > 0,
//	//				(mods & GLFW_MOD_CONTROL) > 0,
//	//				(mods & GLFW_MOD_ALT) > 0,
//	//				(mods & GLFW_MOD_SUPER) > 0,
//	//				(mods & GLFW_MOD_CAPS_LOCK) > 0,
//	//				(mods & GLFW_MOD_NUM_LOCK) > 0,
//	//			};
//	//			itr->second.keyCallback(chord);
//	//		}
//	//	}
//	//}
//
//
//	/*void 
//	Context::nativeCursorPosCallback(GLFWwindow* window, double posX, double posY)
//	{
//		auto ctx = Context::Instance();
//		auto itr = ctx->mRegisteredWindows.find(window);
//		if (itr != ctx->mRegisteredWindows.end())
//		{
//			if (itr->second.keyCallback)
//			{
//				itr->second.cursorPosCallback(posX, posY);
//			}
//		}
//	}
//
//
//	void 
//	Context::nativeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//	{
//		auto ctx = Context::Instance();
//		auto itr = ctx->mRegisteredWindows.find(window);
//		if (itr != ctx->mRegisteredWindows.end())
//		{
//			if (itr->second.keyCallback)
//			{
//				itr->second.mouseButtonCallback({});
//			}
//		}
//	}
//
//
//	void 
//	Context::nativeTextCallback(GLFWwindow* window, unsigned int codepoint)
//	{
//		auto ctx = Context::Instance();
//		auto itr = ctx->mRegisteredWindows.find(window);
//		if (itr != ctx->mRegisteredWindows.end())
//		{
//			if (itr->second.textCallback)
//			{
//				itr->second.textCallback(codepoint);
//			}
//		}
//	}*/
//}
//}