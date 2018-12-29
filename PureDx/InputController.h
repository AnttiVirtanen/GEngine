#pragma once
constexpr auto VK_MULTIPLEKEYSDOWN = 0x99;

// Make singleton template if more singletons occur.
namespace GEngine {
	enum CONTROLS {
		leftArrow = VK_LEFT,
		rightArrow = VK_RIGHT,
		upArrow = VK_UP,
		downArrow = VK_DOWN,
		ctrl = VK_CONTROL,
		space = VK_SPACE,
		multikeys = VK_MULTIPLEKEYSDOWN,
		undefined = 0x100,
		released = 0
	};

	class InputController {
	public:
		static InputController* getInstance();
		void setControlKey(CONTROLS controlKey);
		CONTROLS getControlKey();
		void releaseControl();
	private:
		CONTROLS m_controlKey;
		static InputController* instance;
		InputController();
		~InputController();
		InputController(const InputController&);
	};

}

