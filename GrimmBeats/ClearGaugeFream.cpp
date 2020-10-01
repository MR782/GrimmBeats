#include "ClearGaugeFream.h"
#include"ScreenSystem.h"
#include"SceneManager.h"
#include"GameScene.h"
#include "Lane.h"

void ClearGaugeFream::Initialize()
{
	this->name = "ClearGaugeFream";

	Rect laneRect = sceneManager->FindActor("Lane")->GetDrawRect();

	const int freamwidth = ScreenData::width / 10;
	Point lefttop = Point(Lane::GetLaneRect(LaneName::KLane).x + Lane::GetLaneRect(LaneName::KLane).w + (freamwidth / 2), sceneManager->FindActor("JudgeResultLabel")->GetDrawRect().y);
	this->_drawRect = Rect(lefttop.x, lefttop.y, freamwidth, sceneManager->FindActor("JudgeResultLabel")->GetDrawRect().h);
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
