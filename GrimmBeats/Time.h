#pragma once
#include <Windows.h>

class Time {
public:
	static void Initialize();
	static void Finalize();
	static void Update();

	static LARGE_INTEGER now_time;
	static LARGE_INTEGER start_time;
	static LARGE_INTEGER freq;
};