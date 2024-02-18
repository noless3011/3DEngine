#pragma once
#include <chrono>

class Clock {
public:
	Clock(const Clock&) = delete;
	Clock& operator = (const Clock&) = delete;
	Clock();
	~Clock();
	double Now();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
