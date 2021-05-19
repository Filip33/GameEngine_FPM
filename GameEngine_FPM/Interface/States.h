#pragma once
class States
{
public:
	static bool GetPausedState();
	static void SetPauseState(bool bState);

private:
	static bool bPaused;
};