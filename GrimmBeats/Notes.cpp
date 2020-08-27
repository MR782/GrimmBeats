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
}

void Notes::Update()
{
}

void Notes::Draw()
{
}

JudgeResult Notes::Judge()
{
	return JudgeResult::Miss;
}

void Notes::Move()
{
	//終点の位置 + 終点から始点への方向 * ((判定ラインにくる時間 - 曲の再生時間)*レーンの長さ*スピード);                                    
	//float posY = Model::judge_line->get_position().y + ((this->_perfectTiming - Counter::_gameCnt)
	//	* -(Model::judge_line->get_position().y) * (0.001f * Necessary::speed));
	//this->_position.y = posY;
}
