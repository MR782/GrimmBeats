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
	const int judgetime = 8;

	//判定ラインに到達してから7フレーム以上たったらMiss扱い(キーが押されていなくても)
	if (this->_perfectTiming - Counter::_gameCnt <= -judgetime) {
		this->_judgeFinish = true;
		return JudgeResult::Miss;
	}

	//キーが押された場合の判定----------------------------------------------------------------------------
	if (!KeyBoard::KeyDown(Lane::GetKeyCode(this->_lane))) return JudgeResult::Non;
	JudgeResult result;
	//まだ判定ラインに到達していなくて、判定時間の範囲に入っていないなら
	if (this->_perfectTiming - Counter::_gameCnt > judgetime) return JudgeResult::Non;
	//判定範囲に入っているなら
	else if (abs(this->_perfectTiming - Counter::_gameCnt) > judgetime - 2) result = JudgeResult::Good;//上記以内でX秒以上すぎていたらGood
	else if (abs(this->_perfectTiming - Counter::_gameCnt) > judgetime - 4) result = JudgeResult::Great;//上記以内でX秒以上すぎていたらGreat
	else result = JudgeResult::Perfect;//どれにも当てはまらないならPerfect
	this->_judgeFinish = true;
	return result;
}

