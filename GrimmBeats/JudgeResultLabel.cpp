#include "JudgeResultLabel.h"
#include"ScreenSystem.h"
#include"GameScene.h"

void JudgeResultLabel::Initialize()
{
	this->_drawRect = Rect(0,ScreenData::height / 6,Object::lane->GetRect(LaneName::DLane).x - ScreenData::width / 120,ScreenData::height - ScreenData::height / 3);
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("UIBoard");

	#pragma region テキスト(ラベル)の用意
	this->_resultText[JudgeResult::Perfect] = new Text();
	this->_resultText[JudgeResult::Great] = new Text();
	this->_resultText[JudgeResult::Good] = new Text();
	this->_resultText[JudgeResult::Miss] = new Text();

	const int fontsize = ScreenData::height / 20;
	Point textPos = Point(this->_drawRect.x + fontsize, ScreenData::height / 6 + fontsize);
	this->_resultText[JudgeResult::Perfect]->SetFont("Perfect : %3d", Point(textPos.x,textPos.y), CreateMyFont(fontsize, fontsize / 2, false), SetColor(Color::Yellow));
	this->_resultText[JudgeResult::Great]->SetFont("Great   : %3d", Point(textPos.x, textPos.y + fontsize), CreateMyFont(fontsize, fontsize / 2, false), SetColor(Color::Orange));
	this->_resultText[JudgeResult::Good]->SetFont("Good    : %3d", Point(textPos.x, textPos.y + fontsize * 2), CreateMyFont(fontsize, fontsize / 2, false), SetColor(Color::Green));
	this->_resultText[JudgeResult::Miss]->SetFont("Miss    : %3d", Point(textPos.x, textPos.y + fontsize * 3), CreateMyFont(fontsize, fontsize / 2, false), SetColor(Color::Gray));

#pragma endregion
}

void JudgeResultLabel::Finalize()
{
	this->_anim.reset();

	#pragma region フォントの削除
	this->_resultText[JudgeResult::Perfect]->DeleteFont();
	this->_resultText[JudgeResult::Great]->DeleteFont();
	this->_resultText[JudgeResult::Good]->DeleteFont();
	this->_resultText[JudgeResult::Miss]->DeleteFont();
	delete this->_resultText[JudgeResult::Perfect];
	delete this->_resultText[JudgeResult::Great];
	delete this->_resultText[JudgeResult::Good];
	delete this->_resultText[JudgeResult::Miss];
	this->_resultText.clear();
	#pragma endregion
}

void JudgeResultLabel::Update()
{
}

void JudgeResultLabel::Draw()
{
	this->_anim->ExtendAnimeDraw(this->_drawRect);
	for (auto itr = this->_resultText.begin(); itr != this->_resultText.end(); itr++) {
		(*itr).second->DrawFormatFont(GetJudgeResultCnt((*itr).first));
	}
}

Rect JudgeResultLabel::GetUIBoardRect()
{
	return this->_drawRect;
}


int JudgeResultLabel::GetJudgeResultCnt(JudgeResult  result)
{
	switch (result)
	{
	case JudgeResult::Perfect:
		return 0;
		break;
	case JudgeResult::Great:
		return 0;
		break;
	case JudgeResult::Good:
		return 0;
		break;
	case JudgeResult::Miss:
		return 0;
		break;
	}
	throw("不明な値が入っている/ JudgeResultLabel::GetJudgeResultCnt");
}