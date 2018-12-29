#include "pch.h"
#include "InputController.h"

using namespace GEngine;

InputController::InputController() { }

InputController* InputController::getInstance()
{
	if (InputController::instance == nullptr) {
		InputController::instance = new InputController();
	}
	return InputController::instance;
}

void InputController::setControlKey(CONTROLS controlKey)
{
	m_controlKey = controlKey;
}

void InputController::releaseControl()
{
	m_controlKey = CONTROLS::released;
}

bool InputController::isBeingControlled()
{
	return m_controlKey != CONTROLS::released;
}

InputController::~InputController()
{
	delete InputController::instance;
}

