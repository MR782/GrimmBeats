#pragma once
#include <Windows.h>
#include<iostream>
#include<vector>

class Time {
	struct Timer {
		LARGE_INTEGER now_time;
		LARGE_INTEGER start_time;
		std::string name;

		Timer();
		void Update();
		Timer Create(std::string name);
	};
public:
	static void Initialize();
	static void Finalize();
	static void Update();
	static void CreateTimer(std::string name);
	static LARGE_INTEGER GetTimerNowTime(std::string name);

	static int freamtime;
	static LARGE_INTEGER now_time;
	static LARGE_INTEGER freq;
	static std::vector<Timer> timeArray;
};