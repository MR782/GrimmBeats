#include "TapNotes.h"
#include"GameScene.h"
#include"KeyBoard.h"
#include"./dxlib/DxLib.h"

TapNotes::TapNotes()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("TapNotes");
}

JudgeResult TapNotes::Judge()
{
	if (!KeyBoard::KeyDown(Object::lane->GetKeyCode(this->_lane))) return JudgeResult::Non;
	else if (abs(this->_perfectTiming - 9) > 5) return JudgeResult::Miss;//X秒以上すぎていたらMiss
	else if (abs(this->_perfectTiming - 9) > 4) return JudgeResult::Good;//上記以内でX秒以上すぎていたらGood
	else if (abs(this->_perfectTiming - 9) > 3) return JudgeResult::Great;//上記以内でX秒以上すぎていたらGreat
	return JudgeResult::Perfect;//どれにも当てはまらないならPerfect
}

