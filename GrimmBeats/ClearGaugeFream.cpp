#include "ClearGaugeFream.h"
#include"ScreenSystem.h"
#include"GameScene.h"

void ClearGaugeFream::Initialize()
{
	const int freamwidth = ScreenData::width / 10;
	Point lefttop = Point(Object::lane->GetRect(LaneName::KLane).x + Object::lane->GetRect(LaneName::KLane).w + (freamwidth / 2), Object::judgeResultLabel->GetUIBoardRect().y);
	this->_drawRect = Rect(lefttop.x, lefttop.y, freamwidth, Object::judgeResultLabel->GetUIBoardRect().h);
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("ClearGaugeFream");
}

void ClearGaugeFream::Finalize()
{
	this->_anim.reset();
}

void ClearGaugeFream::Update()
{
}

void ClearGaugeFream::Draw()
{
	this->_anim->ExtendAnimeDraw(this->_drawRect);
}

Rect ClearGaugeFream::GetDrawRect()
{
	return this->_drawRect;
}
