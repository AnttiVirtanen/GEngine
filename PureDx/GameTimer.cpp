#include "pch.h"
#include "GameTimer.h"

using namespace GEngine;

GameTimer::GameTimer() {
	start = std::chrono::system_clock::now();
	step = tick = start;
	clockRate = 1.0 / 60;	// ~0.0166ms
}

double GameTimer::getDifferenceInMS() {
	auto k = std::chrono::duration_cast<std::chrono::milliseconds>(tick - start).count();
	return k;
}

double GameTimer::getClockRate() {
	return clockRate;
}

void GameTimer::clockTick() {
	tick = std::chrono::system_clock::now();
}

double GameTimer::delta() {
	std::chrono::duration<double> ticker = tick - start;
	return ticker.count();
}

void GameTimer::resetClock() {
	clockTick();
	start = tick;
}
