#include "Time.h"

#pragma region Time内変数定義
LARGE_INTEGER  Time::now_time;
LARGE_INTEGER  Time::start_time;
LARGE_INTEGER  Time::freq;
int			   Time::freamtime;
#pragma endregion

void Time::Initialize()
{
	freamtime = 0;
	QueryPerformanceFrequency(&Time::freq);
	QueryPerformanceCounter(&Time::start_time);
	QueryPerformanceCounter(&Time::now_time);
}

void Time::Finalize()
{
}

void Time::Update()
{
	freamtime++;
	//ゲームカウンタの更新
	QueryPerformanceCounter(&Time::now_time);
	//マイクロ秒からミリ秒に変換してフレームに変換
	//Counter::game_cnt = ((now_time.QuadPart - start_time.QuadPart) * 1000) / this->freq.QuadPart / 16.666666667f;//フレーム単位に変換
}
