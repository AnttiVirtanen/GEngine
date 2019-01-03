#pragma once
#include <string>

using namespace std;

namespace GEngine {
	class Debugger {
	public:
		
		template<typename T> static string toStr(T t) {
			return to_string(t);
		}

		template<typename T> static void debugToConsole(T arg1) {
			OutputDebugStringA((arg1 + "\n").c_str());
		}

		template<typename T, typename ... Ts> static void debugToConsole(string str, T base, Ts&&... args) {
			string concatenated = str + ' ' + base;
			debugToConsole(concatenated, args...);
		}

	};
}