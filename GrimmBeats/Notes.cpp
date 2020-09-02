#include "Notes.h"
#include"GameScene.h"

void Notes::Initialize()
{
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
	const int notesHeight = 16;
	this->_perfectTiming = p_timing;
	this->_lane = lane;
	this->holdTime = holdtime;
	//Y座標はMove関数中身と同じにする
	Rect draw = Rect(Object::lane->GetRect(lane).x + 1,//X
		(int)(Object::judgeLine->GetPosition().y + ((this->_perfectTiming - Counter::_gameCnt)* -(Object::judgeLine->GetPosition().y) * (0.001f * (float)Necessary::speed))),//Y
		Object::lane->GetRect(lane).w, notesHeight);//W,H
	this->_drawRect = draw;
}

void Notes::Move()
{
	float posY = Object::judgeLine->GetPosition().y + ((this->_perfectTiming - Counter::_gameCnt)
		* -(Object::judgeLine->GetPosition().y) * (0.001f * (float)Necessary::speed));
	//終点の位置 + 終点から始点への方向 * ((判定ラインにくる時間 - 曲の再生時間)*レーンの長さ*スピード);                                    
	/*
	float posY = Model::judge_line->get_position().y + ((this->_perfectTiming - Counter::_gameCnt)
		* -(Model::judge_line->get_position().y) * (0.001f * Necessary::speed));
	this->_drawRect.y = posY;
	*/
	this->_drawRect.y = (int)posY;
}
