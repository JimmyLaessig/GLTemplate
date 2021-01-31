#pragma once
#include "Base/Enum.h"
#include "Delegate.h"

#include <glm/glm.hpp>
#include <sstream>
#include <string>


namespace Application
{

	ENUM_CLASS(Key,
		SPACE,
		APOSTROPHE,
		COMMA,
		MINUS,
		PERIOD,
		SLASH,
		ZERO ,
		ONE ,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		SEMICOLON,
		EQUAL,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		LEFT_BRACKET,
		BACKSLASH ,
		RIGHT_BRACKET,
		GRAVE_ACCENT,
		WORLD_1,
		WORLD_2,
		ESCAPE,
		ENTER,
		TAB,
		BACKSPACE,
		INSERT,
		DELETE,
		RIGHT,
		LEFT,
		DOWN,
		UP,
		PAGE_UP,
		PAGE_DOWN,
		HOME,
		END,
		CAPS_LOCK,
		SCROLL_LOCK,
		NUM_LOCK,
		PRINT_SCREEN,
		PAUSE,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		F25,
		KP_0,
		KP_1,
		KP_2,
		KP_3,
		KP_4,
		KP_5,
		KP_6,
		KP_7,
		KP_8,
		KP_9,
		KP_DECIMAL,
		KP_DIVIDE,
		KP_MULTIPLY,
		KP_SUBTRACT,
		KP_ADD,
		KP_ENTER,
		KP_EQUAL,
		LEFT_SHIFT,
		LEFT_CONTROL,
		LEFT_ALT,
		LEFT_SUPER,
		RIGHT_SHIFT,
		RIGHT_CONTROL,
		RIGHT_ALT,
		RIGHT_SUPER,
		MENU,
		UNKNOWN
	);



	ENUM_CLASS(MouseButton,
		BUTTON_1,
		BUTTON_2,
		BUTTON_3,
		BUTTON_4,
		BUTTON_5,
		BUTTON_6,
		BUTTON_7,
		BUTTON_8,
	);


	ENUM_CLASS(KeyState,
		RELEASED,
		PRESSED,
		REPEAT
	);


	struct InputChord
	{
		Key key;							// The key of the chord
		KeyState state{ KeyState::PRESSED };// The state of the key

		bool shift{ false };				// Wether the SHIFT key is pressed
		bool ctrl{ false };					// Wether the CTRL key is pressed
		bool alt{ false };					// Wether the ALT key is pressed
		bool super{ false };				// Whether the SUPER key is pressed (e.g. Windows key)
		bool capslock{ false };				// Whether capslock is active
		bool numlock{ false };				// Whether numlock is active


		std::string toString() const
		{
			auto toString = [](bool b){ return b ? "true" : "false"; };
			
			std::stringstream s;
			s << "key=" << enumToString(key) << ",";
			s << "state" << enumToString(state) << ",";
			s << "shift=" << toString(shift) << ",";
			s << "ctrl=" << toString(ctrl) << ",";
			s << "alt=" << toString(alt) << ",";
			s << "super=" << toString(super) << ",";
			s << "capslock=" << toString(capslock) << ",";
			s << "numlock=" << toString(numlock);

			std::string res;
			s.str(res);
			return res;
		}
	};


	class IInput
	{
	public:
		
		// Gets the current state of the key
		virtual KeyState getKeyState(Key key) = 0;

		// Gets the current state of the mouse button
		virtual KeyState getMouseButtonStae(MouseButton button) = 0;

		// Returns the cursor's position in pixel
		virtual glm::u32vec2 getCursorPosition() const = 0;

		// Delegate
		virtual IDelegate<InputChord>& onKeyPressedEvent() = 0;

		// Delegate
		virtual IDelegate<InputChord>& onCursorMoveEvent() = 0;
	};
}