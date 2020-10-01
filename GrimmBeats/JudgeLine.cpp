#include "JudgeLine.h"
#include"GameScene.h"
#include "BasicUI.h"
#include"ScreenSystem.h"
#include"Lane.h"
#include"./dxlib/DxLib.h"

void JudgeLine::Initialize()
{
	this->name = "JudgeLine";
	this->_anim = nullptr;
	this->_position = Vector2(Lane::GetLaneRect(LaneName::DLane).x,
		Lane::GetLaneRect(LaneName::DLane).y + Lane::GetLaneRect(LaneName::DLane).h - (ScreenData::height / 6));
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
		Lane::GetLaneRect(LaneName::KLane).x + Lane::GetLaneRect(LaneName::KLane).w,
		(int)this->_position.y + judgeLineHeight, SetColor(Color::Red), TRUE);
}
