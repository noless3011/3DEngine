#include "Clock.h"

Clock::Clock()
{
	start = std::chrono::high_resolution_clock::now();
}

Clock::~Clock()
{
}


double Clock::Now()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
	return (double)duration.count() / static_cast<double>(1000);
}
