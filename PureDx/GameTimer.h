#pragma once

#include <chrono>
#include "Debugger.h"

typedef std::chrono::time_point<std::chrono::system_clock> timePoint;

// Proto, rewrite later.
namespace GEngine {
	class GameTimer {
	public:
		GameTimer();

		template<typename Callback> void runTimer(const Callback& update) {
			if (getDifferenceInMS() >= getClockRate()) {
				resetClock();
				update();
			}
			clockTick();
		};

		void clockTick();
		void resetClock();
		
		double getClockRate();
		double getDifferenceInMS();
		
		double delta();
	private:
		timePoint step;
		timePoint start;
		timePoint tick;

		double clockRate;
	};
}
