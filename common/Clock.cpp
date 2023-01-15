#include "Clock.h"

Clock::Clock(){}

void Clock::StartCounter()
{
	// Metemos la frecuencia de la procesador en los ticks
	if (!QueryPerformanceFrequency(&ticks))
		printf("QueryPerformanceFrequency failed!\n");

	// Number of ticks per milisecond
	pcFrequency = double(ticks.QuadPart)/1000.f;

	// Number of ticks from the starting moment
	QueryPerformanceCounter(&ticks);
	startCounter = ticks.QuadPart;
}

double Clock::GetCounter()
{
	//Number of miliseconds since StartCounter was called
	QueryPerformanceCounter(&ticks);
	return double(ticks.QuadPart/ pcFrequency);
}