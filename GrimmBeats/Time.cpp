#include "Time.h"

#pragma region Time���ϐ���`
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
	//�Q�[���J�E���^�̍X�V
	QueryPerformanceCounter(&Time::now_time);
	//�}�C�N���b����~���b�ɕϊ����ăt���[���ɕϊ�
	//Counter::game_cnt = ((now_time.QuadPart - start_time.QuadPart) * 1000) / this->freq.QuadPart / 16.666666667f;//�t���[���P�ʂɕϊ�
}
