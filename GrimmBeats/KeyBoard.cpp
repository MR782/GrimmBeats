#include "KeyBoard.h"
#include"./dxlib/DxLib.h"

#define KEY_BOARD_BUF 256
//実体化
char* KeyBoard::current;
char* KeyBoard::previous;

void KeyBoard::Initialize()
{
	//領域確保
	current = new char[KEY_BOARD_BUF];
	previous = new char[KEY_BOARD_BUF];
}

void KeyBoard::Finalize()
{
	//領域開放
	delete[] current;
	delete[] previous;
}

void KeyBoard::Update()
{
	//作業領域と１フレーム前の入れ替え
	static char* work;

	work = current;     
	current = previous;  
	previous = work;    

	GetHitKeyStateAll(current);
}

bool KeyBoard::KeyDown(int k_)
{
	//今は押されているが１フレーム前は押されていない
	return *(current + k_) == 1 && *(previous + k_) == 0;
}

bool KeyBoard::KeyUp(int k_)
{
	//今は押されていないが1フレーム前は押されていた
	return *(current + k_) == 0 && *(previous + k_) == 1;
}

bool KeyBoard::KeyPress(int k_)
{
	//今現在押されているなら
	return *(current + k_) == 1;
}