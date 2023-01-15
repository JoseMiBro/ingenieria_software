#pragma once
#include <windows.h>
#include <stdio.h>

class Clock
{
private:
	LARGE_INTEGER ticks;
	__int64 startCounter;
public:

	double pcFrequency = 0;
	
	Clock();

	void StartCounter();

	double GetCounter();
};

