#include "SpeedLabel.h"
#include"ScreenSystem.h"
#include"Necessary.h"
#include"KeyBoard.h"
#include"./dxlib/DxLib.h"

SpeedLabel::SpeedLabel()
{
	this->_text = nullptr;
}

void SpeedLabel::Initialize()
{
	this->name = "SpeedLabel";
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("TxtBox");
	// 1048:600
	this->_drawRect = Rect(0, ScreenData::height / 2 + ScreenData::height / 10,
		(ScreenData::width / 2), ScreenData::height / 10);
	#pragma region テキスト(ラベルの生成・初期化)
	this->_text = new Text();
	this->_text->SetFont("SPEED : <(DF) %2d (JK)>", Point(this->_drawRect.x + 5, this->_drawRect.y + 10), CreateMyFont((ScreenData::height / 10) - 25, 16, false), SetColor(Color::Black));
	#pragma endregion
}

void SpeedLabel::Finalize()
{
	this->_text->DeleteFont();
	delete this->_text;
}

void SpeedLabel::Update()
{
	if (KeyBoard::KeyDown(KEY_INPUT_J) || KeyBoard::KeyDown(KEY_INPUT_K)) Necessary::speed = min(20, Necessary::speed + 1);
	if (KeyBoard::KeyDown(KEY_INPUT_D) || KeyBoard::KeyDown(KEY_INPUT_F)) Necessary::speed = max(1, Necessary::speed - 1);
}

void SpeedLabel::Draw()
{
	this->_anim->ExtendAnimeDraw(_drawRect);
	this->_text->DrawFormatFont(Necessary::speed);
}
