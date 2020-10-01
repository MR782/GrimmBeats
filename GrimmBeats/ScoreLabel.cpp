#include "ScoreLabel.h"
#include"ScreenSystem.h"
#include"GameScene.h"
#include"SceneManager.h"

ScoreLabel::ScoreLabel()
{
	this->_socreLabel = nullptr;
}

void ScoreLabel::Initialize()
{
	this->name = "ScoreLabel";
	this->_socreLabel = new Text();
	int strSize = ScreenData::width / 30;

	Rect uiBoardRect = sceneManager->FindActor("JudgeResultLabel")->GetDrawRect();

	this->_socreLabel->SetFont("SCORE : %6d",
		Point(uiBoardRect.x + (strSize / 2),
			uiBoardRect.y + uiBoardRect.h - (strSize * 5)),
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
