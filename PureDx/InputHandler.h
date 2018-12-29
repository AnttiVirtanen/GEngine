#pragma once
#include <vector>
#include "InputController.h"
#include "Drawable.h"

namespace GEngine {
	// Option to pass inputController?
	class InputHandler
	{
	public:
		InputHandler();
		void setControl(WPARAM wParam);
		CONTROLS getControl();
		void releaseControl();
	private:
		InputController* controller;
	};
}

