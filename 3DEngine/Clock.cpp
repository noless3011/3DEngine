#include "Clock.h"

std::chrono::time_point<std::chrono::high_resolution_clock> Clock::start = std::chrono::high_resolution_clock::now();
float Clock::deltaTime = 0.00001;
float Clock::cur;
float Clock::pre;
Clock::Clock()
{
	pre = 0;
	cur = 0;

}

Clock::~Clock()
{
}


Clock& Clock::GetClock()
{
	static Clock clock;
	return clock;
}

double Clock::Now()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - Clock::start);
	return (double)duration.count() / static_cast<double>(1000);
}

void Clock::CalculateDeltaTime()
{
	pre = cur;
	cur = Clock::Now();
	deltaTime = cur - pre;
}
