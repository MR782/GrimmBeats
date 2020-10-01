#pragma once
#include <Windows.h>
#include<iostream>
#include<vector>

class Time {
public:
	enum class TimeFormat {
		Fream,
		Millisecond
	};
private:
	struct Timer {
		LARGE_INTEGER now_time;
		LARGE_INTEGER freq;
		LARGE_INTEGER start_time;
		std::string name;

		Timer();
		void Update();
		Timer Create(std::string name);
		float ElapsedTime(TimeFormat format);
	};
public:
	static void Initialize();
	static void Finalize();
	static void Update();
	static void CreateTimer(std::string name);
	static void DeleteTimer(std::string name);
	static LARGE_INTEGER GetTimerNowTime(std::string name);

	static int freamtime;
	static LARGE_INTEGER now_time;
	static LARGE_INTEGER freq;
	static std::vector<Timer> timeArray;
	static float GetElapsedTime(std::string name, TimeFormat format);
};