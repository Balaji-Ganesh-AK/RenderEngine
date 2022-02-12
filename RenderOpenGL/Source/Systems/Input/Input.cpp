#include "Input.h"

#include "Windows/WindowsInput.h"

KREngine::FInput* KREngine::FInput::Create(WindowsWindow* pointer)
{
	return new WindowsInput(pointer);
}
