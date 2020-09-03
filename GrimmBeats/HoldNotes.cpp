#include "HoldNotes.h"
#include"KeyBoard.h"
#include"GameScene.h"
#include"./dxlib/DxLib.h"

HoldNotes::HoldNotes()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("HoldNotes");
	this->_state = HoldState::Non;
	this->_holdCnt = 0;
}

JudgeResult HoldNotes::Judge()
{
	const int judgetime = 7;
	//先頭タップ判定----------------------------------------------------
	if (this->_state == HoldState::Non) {
		JudgeResult result;
		//通り過ぎた時の判定(Miss)
		if (this->_perfectTiming - Counter::_gameCnt <= -judgetime) { 
			this->_state = HoldState::Hold;
			return JudgeResult::Miss;
		}
		if (KeyBoard::KeyDown(Object::lane->GetKeyCode(this->_lane))) {
			//まだ判定ラインに到達していなくて、判定時間の範囲に入っていないなら
			if (this->_perfectTiming - Counter::_gameCnt > judgetime) return JudgeResult::Non;
			//判定範囲に入っているなら
			else if (this->_perfectTiming - Counter::_gameCnt > judgetime) result = JudgeResult::Miss;//X秒以上すぎていたらMiss
			else if (this->_perfectTiming - Counter::_gameCnt > judgetime - 3) result = JudgeResult::Good;//上記以内でX秒以上すぎていたらGood
			else if (this->_perfectTiming - Counter::_gameCnt > judgetime - 5) result = JudgeResult::Great;//上記以内でX秒以上すぎていたらGreat
			else result = JudgeResult::Perfect;//どれにも当てはまらないならPerfect
			this->_state = HoldState::Hold;
			return result;
		}
	}
	//ホールド判定------------------------------------------------------
	else {
		if (KeyBoard::KeyPress(Object::lane->GetKeyCode(this->_lane))) {
			this->_holdCnt++;
			JudgeResult result;

			if (this->_perfectTiming + this->_holdTime < Counter::_gameCnt) this->_judgeFinish = true;
			if (this->_holdCnt % 2 == 0) result = JudgeResult::Perfect;
			else result = JudgeResult::HoldNow;
			return result;
		}
	}
	return JudgeResult::Non;
}
