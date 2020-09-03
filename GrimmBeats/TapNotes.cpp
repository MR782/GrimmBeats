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
	const int judgetime = 7;

	//判定ラインに到達してから7フレーム以上たったらMiss扱い(キーが押されていなくても)
	if (this->_perfectTiming - Counter::_gameCnt <= -judgetime) return JudgeResult::Miss;

	//キーが押された場合の判定----------------------------------------------------------------------------
	if (!KeyBoard::KeyDown(Object::lane->GetKeyCode(this->_lane))) return JudgeResult::Non;
	JudgeResult result;
	//まだ判定ラインに到達していなくて、判定時間の範囲に入っていないなら
	if (this->_perfectTiming - Counter::_gameCnt > judgetime) return JudgeResult::Non;
	//判定範囲に入っているなら
	else if (abs(this->_perfectTiming - Counter::_gameCnt) > judgetime) result = JudgeResult::Miss;//X秒以上すぎていたらMiss
	else if (abs(this->_perfectTiming - Counter::_gameCnt) > judgetime - 3) result = JudgeResult::Good;//上記以内でX秒以上すぎていたらGood
	else if (abs(this->_perfectTiming - Counter::_gameCnt) > judgetime - 5) result = JudgeResult::Great;//上記以内でX秒以上すぎていたらGreat
	else result = JudgeResult::Perfect;//どれにも当てはまらないならPerfect
	this->_judgeFinish = true;
	return result;
}

