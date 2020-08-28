#include "Time.h"

#pragma region Time���ϐ���`
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
	//�Q�[���J�E���^�̍X�V
	QueryPerformanceCounter(&Time::now_time);
	for (auto itr = timeArray.begin(); itr != timeArray.end(); itr++) {

	}
	//�}�C�N���b����~���b�ɕϊ����ăt���[���ɕϊ�
	//Counter::game_cnt = ((now_time.QuadPart - start_time.QuadPart) * 1000) / this->freq.QuadPart / 16.666666667f;//�t���[���P�ʂɕϊ�
}

void Time::CreateTimer(std::string name)
{
	Timer timer;
	timeArray.push_back(timer.Create(name));
}

LARGE_INTEGER Time::GetTimerNowTime(std::string name)
{
	for (auto itr = timeArray.begin(); itr != timeArray.end(); itr++) {
		if ((*itr).name == name) return (*itr).now_time;
	}
	throw("�w�肳�ꂽ�^�C�}�[��������܂���");
}

Time::Timer::Timer()
{
	this->now_time.QuadPart = 0;
	this->start_time.QuadPart = 0;
}

void Time::Timer::Update()
{
	QueryPerformanceCounter(&this->now_time);
}

Time::Timer Time::Timer::Create(std::string name)
{
	Timer timer;
	QueryPerformanceCounter(&timer.start_time);
	QueryPerformanceCounter(&timer.now_time);
	return Timer();
}
