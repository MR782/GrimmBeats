#include "Mouse.h"
#include"./dxlib/DxLib.h"

//左クリック
int Mouse::left_previous;//1フレーム前
int Mouse::left_current;//作業領域
//右クリック用
int Mouse::right_previous;//１フレーム前
int Mouse::right_current;//作業領域

void Mouse::Initialize()
{
	//初期化
	left_current = 0;
	left_previous = 0;
	right_current = 0;
	right_previous = 0;
}

void Mouse::Update()
{
	//1フレーム前のマウスの状態
	left_previous = left_current;
	right_previous = right_current;
	//クリック判定
	left_current = (GetMouseInput() & MOUSE_INPUT_LEFT);
	right_current = (GetMouseInput() & MOUSE_INPUT_RIGHT);
}

//---------------------------------------------------------------------------
//左クリック
//---------------------------------------------------------------------------
bool Mouse::LeftClickDown()
{
	return left_previous == 0 && left_current != 0;
}

bool Mouse::LeftClickUp()
{
	return left_previous != 0 && left_current == 0;
}

bool Mouse::LeftClickPress()
{
	return left_current != 0 && left_previous != 0;
}

bool Mouse::LeftClickNotPress()
{
	return left_current == 0 && left_previous == 0;
}
//---------------------------------------------------------------------------
//右クリック
//---------------------------------------------------------------------------
bool Mouse::RightClickDown()
{
	return right_previous == 0 && right_current != 0;
}

bool Mouse::RightClickUp()
{
	return right_previous != 0 && right_current == 0;
}

bool Mouse::RightClickPress()
{
	return right_previous != 0 && right_current != 0;
}

bool Mouse::RightClickNotPress()
{
	return right_previous == 0 && right_current == 0;
}
