#include "JudgeLine.h"
#include"GameScene.h"
#include "BasicUI.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

void JudgeLine::Initialize()
{
	this->_anim = nullptr;
	this->_position = Vector2(Object::lane->GetRect(LaneName::DLane).x,
		Object::lane->GetRect(LaneName::DLane).y + Object::lane->GetRect(LaneName::DLane).h - (ScreenData::height / 6));
}

void JudgeLine::Finalize()
{
}

void JudgeLine::Update()
{
}

void JudgeLine::Draw()
{
	const int judgeLineHeight = 8;
	DrawBox((int)this->_position.x, (int)this->_position.y,
		Object::lane->GetRect(LaneName::KLane).x + Object::lane->GetRect(LaneName::KLane).w,
		(int)this->_position.y + judgeLineHeight, SetColor(Color::Red), TRUE);
}
