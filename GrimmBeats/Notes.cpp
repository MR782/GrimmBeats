#include "Notes.h"
#include"GameScene.h"
#include"SceneManager.h"

Notes::Notes()
{
	this->_holdTime = 0;
	this->_judgeFinish = false;
	this->_lane = LaneName::DLane;
	this->_perfectTiming = 0;
}

void Notes::Initialize()
{
	this->name = "Notes";
	this->_lane = LaneName::SPACELane;
	this->_perfectTiming = 0;
	this->_position = Vector2();
}

void Notes::Finalize()
{
	this->_anim.reset();
}

void Notes::Update()
{
	this->Move();
}

void Notes::Draw()
{
	this->_anim->ExtendAnimeDraw(this->_drawRect);
}

LaneName Notes::GetLane()
{
	return this->_lane;
}

void Notes::SetInfo(float p_timing, LaneName lane, float holdtime)
{
	float notesHeight = 16;

	this->_perfectTiming = p_timing;
	this->_lane = lane;
	this->_holdTime = holdtime;
	this->_judgeFinish = false;
	//YÀ•W‚ÍMoveŠÖ”’†g‚Æ“¯‚¶‚É‚·‚é
	Vector2 judgeLinePos = sceneManager->FindActor("JudgeLine")->GetPosition();

	Rect draw = Rect(Lane::GetLaneRect(lane).x + 1,//X
		(int)(judgeLinePos.y + ((this->_perfectTiming - Counter::_gameCnt) * -(judgeLinePos.y) * (0.001f * (float)Necessary::speed))),//Y
		Lane::GetLaneRect(lane).w, (int)-notesHeight);//W,H
	this->_drawRect = draw;
}

bool Notes::GetJudgeFinish()
{
	return this->_judgeFinish;
}

void Notes::Move()
{
	Vector2 judgeLinePos = sceneManager->FindActor("JudgeLine")->GetPosition();
	float posY = judgeLinePos.y + ((this->_perfectTiming - Counter::_gameCnt)
		* -(judgeLinePos.y) * (0.001f * (float)Necessary::speed));

	this->_drawRect.y = (int)posY;
}
