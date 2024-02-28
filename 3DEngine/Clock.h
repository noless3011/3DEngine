#pragma once
#include <chrono>

class Clock {
	friend class App;
public:
	static float deltaTime;
public:
	static Clock& GetClock();

	static double Now();
private:
	static void CalculateDeltaTime();
	Clock(const Clock&) = delete;
	Clock& operator = (const Clock&) = delete;
	Clock();
	~Clock();
private:
	static float pre, cur;
	static std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
