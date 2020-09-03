#include "ScoreLabel.h"
#include"ScreenSystem.h"
#include"GameScene.h"

ScoreLabel::ScoreLabel()
{
	this->_socreLabel = nullptr;
}

void ScoreLabel::Initialize()
{
	this->_socreLabel = new Text();
	int strSize = ScreenData::width / 30;
	this->_socreLabel->SetFont("SCORE : %6d",
		Point(Object::judgeResultLabel->GetUIBoardRect().x + (strSize / 2),
			Object::judgeResultLabel->GetUIBoardRect().y + Object::judgeResultLabel->GetUIBoardRect().h - (strSize * 5)),
		CreateMyFont(strSize, strSize / 2, false), SetColor(Color::Black));
}

void ScoreLabel::Finalize()
{
	this->_socreLabel->DeleteFont();

	delete this->_socreLabel;
}

void ScoreLabel::Update()
{
}

void ScoreLabel::Draw()
{
	this->_socreLabel->DrawFormatFont(Counter::_score);
}
