#include "pch.h"
#include "InputHandler.h"

using namespace GEngine;

InputController* InputController::instance = nullptr;

void InputHandler::setControl(WPARAM wParam)
{
	CONTROLS controlKey = static_cast<CONTROLS>(wParam);
	controller->setControlKey(controlKey);
}

CONTROLS InputHandler::getControl()
{
	return controller->getControlKey();
}

void InputHandler::releaseControl()
{
	controller->releaseControl();
}

InputHandler::InputHandler()
{
	controller = InputController::getInstance();
}

