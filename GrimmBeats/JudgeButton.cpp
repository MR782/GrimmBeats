#include "JudgeButton.h"
#include"ScreenSystem.h"
#include"GameScene.h"
#include"KeyBoard.h"
#include"./dxlib/DxLib.h"

void JudgeButton::Initialize()
{
	this->_buttons.push_back(JudgeButtonItem("DPush", "DNotPush", Rect(Object::lane->GetRect(LaneName::DLane)),KEY_INPUT_D));
	this->_buttons.push_back(JudgeButtonItem("FPush", "FNotPush", Rect(Object::lane->GetRect(LaneName::FLane)), KEY_INPUT_F));
	this->_buttons.push_back(JudgeButtonItem("JPush", "JNotPush", Rect(Object::lane->GetRect(LaneName::JLane)), KEY_INPUT_J));
	this->_buttons.push_back(JudgeButtonItem("KPush", "KNotPush", Rect(Object::lane->GetRect(LaneName::KLane)), KEY_INPUT_K));
	this->_buttons.push_back(JudgeButtonItem("SpacePush", "SpaceNotPush", Rect(Object::lane->GetRect(LaneName::SPACELane)), KEY_INPUT_SPACE));
}

void JudgeButton::Finalize()
{
	this->_buttons.clear();
}

void JudgeButton::Update()
{
	for (auto itr = this->_buttons.begin(); itr != this->_buttons.end(); itr++) {
		ButtonGraphChange((*itr));
	}
}

void JudgeButton::Draw()
{
	const int judgeLineHeight = 16;
	for (auto itr = this->_buttons.begin(); itr != this->_buttons.end(); itr++) {
		Rect laneRect = (*itr).drawRect;
		(*itr).anime->ExtendAnimeDraw(Rect((float)laneRect.x, laneRect.y + laneRect.h - Object::judgeLine->GetPosition().y + judgeLineHeight,
			(float)laneRect.w, ScreenData::height - laneRect.y + laneRect.h - Object::judgeLine->GetPosition().y + judgeLineHeight));
	}
}

JudgeButton::JudgeButtonItem::JudgeButtonItem(std::string push_, std::string notPush_, Rect draw_,int key_)
{
	this->drawRect = draw_;
	this->notPushGraphName = notPush_;
	this->pushGraphName = push_;
	this->anime = std::make_unique<Animation>();
	this->key = key_;
	this->anime->Set("this->notPushGraphName");
}

void JudgeButton::ButtonGraphChange(JudgeButtonItem& item)
{
	if (KeyBoard::KeyPress(item.key)) {
		item.anime->Set(item.pushGraphName);
	}
	else {
		item.anime->Set(item.notPushGraphName);
	}
}