#include "pch.h"
#include "InputProxy.h"

using namespace GEngine;

InputProxy* InputProxy::instance = nullptr;

InputProxy::InputProxy() { }

InputProxy* InputProxy::getInstance()
{
	if (InputProxy::instance == nullptr) {
		InputProxy::instance = new InputProxy();
	}
	return InputProxy::instance;
}

void InputProxy::setControlKey(CONTROLS controlKey)
{
	m_controlKey = controlKey;
}

CONTROLS InputProxy::getControlKey()
{
	return m_controlKey;
}

void InputProxy::releaseControl()
{
	m_controlKey = CONTROLS::released;
}

InputProxy::~InputProxy()
{
	delete InputProxy::instance;
}

