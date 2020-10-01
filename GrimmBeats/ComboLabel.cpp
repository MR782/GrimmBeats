#include "ComboLabel.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"Lane.h"
#include"ScreenSystem.h"

ComboLabel::ComboLabel()
{
	this->_comboLabel = nullptr;
}

void ComboLabel::Initialize()
{
	this->name = "ComboLabel";
	this->_comboLabel = new Text();

	int strSize = ScreenData::width / 30;
	int strwitdhhalf = ((int)strlen("Combo") * strSize) / 2;

	Rect laneRect = Lane::GetLaneRect(LaneName::SPACELane);

	this->_comboLabel->SetFont("Combo\n%d",
		Point(laneRect.x + ((laneRect.w - strwitdhhalf) / 2),(ScreenData::height / 3) - (strSize / 2)),
		CreateMyFont(strSize, strSize / 2, false), SetColor(Color::White));
}

void ComboLabel::Finalize()
{
	this->_comboLabel->DeleteFont();

	delete this->_comboLabel;
}

void ComboLabel::Update()
{
}

void ComboLabel::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 175);
	this->_comboLabel->DrawFormatFont(Counter::_comboCnt);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);
}
