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

	class InputProxy {
	public:
		static InputProxy* getInstance();
		void setControlKey(CONTROLS controlKey);
		CONTROLS getControlKey();
		void releaseControl();
	private:
		CONTROLS m_controlKey;
		static InputProxy* instance;
		InputProxy();
		~InputProxy();
		InputProxy(const InputProxy&);
	};

}

