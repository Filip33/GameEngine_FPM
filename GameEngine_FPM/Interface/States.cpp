#include "States.h"

bool States::bPaused = false;

bool States::GetPausedState()
{
	return States::bPaused;
}

void States::SetPauseState(bool bState)
{
	bPaused = bState;
}