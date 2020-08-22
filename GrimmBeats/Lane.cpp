#include "Lane.h"
#include"ScreenSystem.h"
#include"BasicUI.h"
#include"./dxlib/DxLib.h"

Lane::~Lane()
{
}

void Lane::Initialize()
{
	#pragma region レーンごとの矩形を用意
	this->_lane[LaneName::DLane] = Rect();
	this->_lane[LaneName::FLane] = Rect();
	this->_lane[LaneName::SPACELane] = Rect();
	this->_lane[LaneName::JLane] = Rect();
	this->_lane[LaneName::KLane] = Rect();
	#pragma endregion

	#pragma region レーンごとの対応キーをセット
	this->_keycode[LaneName::DLane] = KEY_INPUT_D;
	this->_keycode[LaneName::FLane] = KEY_INPUT_F;
	this->_keycode[LaneName::SPACELane] = KEY_INPUT_SPACE;
	this->_keycode[LaneName::JLane] = KEY_INPUT_J;
	this->_keycode[LaneName::KLane] = KEY_INPUT_K;
	#pragma endregion

	this->_anim = nullptr;
	this->_blink = false;
}

void Lane::Finalize()
{
	this->_keycode.clear();
	this->_lane.clear();
}

void Lane::Update()
{
}

void Lane::Draw()
{
	for (auto itr = this->_lane.begin(); itr != this->_lane.end();itr++) {
		//Map内からLaneNameを取り出してそれに位置するRectを取り出して代入
		Rect rect = (*this->_lane.find(LaneName((*itr).first))).second;
		DrawBox(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, SetColor(Color::Black), FALSE);
	}
}

std::map<LaneName,int> Lane::GetKeyCode()
{
	return this->_keycode;
}
