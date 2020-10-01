#include "Time.h"

#pragma region Time内変数定義
LARGE_INTEGER  Time::now_time;
LARGE_INTEGER  Time::freq;
int			   Time::freamtime;
std::vector<Time::Timer> Time::timeArray;
#pragma endregion

void Time::Initialize()
{
	freamtime = 0;
	QueryPerformanceFrequency(&Time::freq);
	QueryPerformanceCounter(&Time::now_time);
	timeArray.clear();
}

void Time::Finalize()
{
	timeArray.clear();
}

void Time::Update()
{
	freamtime++;
	//ゲームカウンタの更新
	QueryPerformanceCounter(&Time::now_time);
	for (auto itr = timeArray.begin(); itr != timeArray.end(); itr++) {
		(*itr).Update();
	}
	//マイクロ秒からミリ秒に変換してフレームに変換
	//Counter::game_cnt = ((now_time.QuadPart - start_time.QuadPart) * 1000) / this->freq.QuadPart / 16.666666667f;//フレーム単位に変換
}

void Time::CreateTimer(std::string name)
{
	Timer timer;
	timeArray.push_back(timer.Create(name));
}

void Time::DeleteTimer(std::string name)
{
	for (auto itr = timeArray.begin(); itr != timeArray.end(); itr++) {
		if ((*itr).name == name) { 
			timeArray.erase(itr);
			break;
		}
	}
}

LARGE_INTEGER Time::GetTimerNowTime(std::string name)
{
	for (auto itr = timeArray.begin(); itr != timeArray.end(); itr++) {
		if ((*itr).name == name) return (*itr).now_time;
	}
	throw("指定されたタイマーが見つかりません");
}

float Time::GetElapsedTime(std::string name, TimeFormat format)
{
	for (auto itr = timeArray.begin(); itr != timeArray.end(); itr++) {
		if ((*itr).name != name) continue;
		return (*itr).ElapsedTime(format);
	}
	return 0;
}

Time::Timer::Timer()
{
	this->now_time.QuadPart = 0;
	this->start_time.QuadPart = 0;
	this->freq.QuadPart = 0;
}

void Time::Timer::Update()
{
	QueryPerformanceCounter(&this->now_time);
}

Time::Timer Time::Timer::Create(std::string name)
{
	//既に存在するなら作成しない
	for (auto itr = timeArray.begin(); itr != timeArray.end(); itr++) {
		if ((*itr).name == name)return Timer();
	}
	Timer timer;
	timer.name = name;
	QueryPerformanceCounter(&timer.start_time);
	QueryPerformanceCounter(&timer.now_time);
	QueryPerformanceFrequency(&timer.freq);
	return timer;
}

float Time::Timer::ElapsedTime(TimeFormat format)
{
	float time = 0;
	switch (format)
	{
	case Time::TimeFormat::Fream:
		time = ((this->now_time.QuadPart - this->start_time.QuadPart) * 1000) / this->freq.QuadPart / 16.666666667f;//フレーム単位に変換
		break;
	case Time::TimeFormat::Millisecond:
		time = (((float)(now_time.QuadPart - start_time.QuadPart)) * 1000) / (float)this->freq.QuadPart;
		break;
	}
	return time;
}
