#include "Lane.h"
#include"ScreenSystem.h"
#include"BasicUI.h"
#include"KeyBoard.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"./dxlib/DxLib.h"

std::map<LaneName, Rect> Lane::_lane;
std::map<LaneName, int> Lane::_keycode;

Lane::~Lane()
{
}

void Lane::Initialize()
{
	this->name = "Lane";
	const int laneXsize = (ScreenData::width / 14);
	const int spaceLaneXsize = laneXsize * 2;
	#pragma region レーンごとの矩形を用意
	this->_lane[LaneName::DLane] = Rect(ScreenData::width / 2 - laneXsize - laneXsize * 2, 0, laneXsize, ScreenData::height);
	this->_lane[LaneName::FLane] = Rect(ScreenData::width / 2 - laneXsize - laneXsize, 0, laneXsize, ScreenData::height);
	this->_lane[LaneName::SPACELane] = Rect(ScreenData::width / 2 - spaceLaneXsize / 2,0,spaceLaneXsize,ScreenData::height);
	this->_lane[LaneName::JLane] = Rect(ScreenData::width / 2 + laneXsize, 0, laneXsize, ScreenData::height);
	this->_lane[LaneName::KLane] = Rect(ScreenData::width / 2 + laneXsize + laneXsize, 0, laneXsize, ScreenData::height);
	#pragma endregion

	#pragma region レーンごとの対応キーをセット
	this->_keycode[LaneName::DLane] = KEY_INPUT_D;
	this->_keycode[LaneName::FLane] = KEY_INPUT_F;
	this->_keycode[LaneName::SPACELane] = KEY_INPUT_SPACE;
	this->_keycode[LaneName::JLane] = KEY_INPUT_J;
	this->_keycode[LaneName::KLane] = KEY_INPUT_K;
	#pragma endregion

	this->_anim = nullptr;
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
		DrawBox(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, SetColor(Color::Black),TRUE);
		DrawWhiteLane((*itr).first);
		DrawLine(rect.x, rect.y, rect.x, rect.y + rect.h, SetColor(Color::White));
		DrawLine(rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h, SetColor(Color::White));
	}
}

Rect Lane::GetLaneRect(LaneName lane)
{

	for (auto itr = _lane.begin(); itr != _lane.end(); itr++) {
		if ((*itr).first == lane) return _lane.find(LaneName((*itr).first))->second;
	}
	throw("指定された矩形が見つかりませんでした(Lane::GetRect())");
}

int Lane::GetKeyCode(LaneName lane)
{
	return _keycode[lane];
}

bool Lane::IsPressed(LaneName lane)
{
	return KeyBoard::KeyPress(this->_keycode[lane]);
}

void Lane::DrawWhiteLane(LaneName lane)
{
	Vector2 pos = sceneManager->FindActor("JudgeLine")->GetPosition();
	if (IsPressed(lane)) {
		DrawBox(this->_lane[lane].x, this->_lane[lane].y + ScreenData::height / 6,
			this->_lane[lane].x + this->_lane[lane].w, this->_lane[lane].y + (int)pos.y,
			SetColor(Color::Gray), TRUE);
	}
}