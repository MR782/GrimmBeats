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
	//�擪�^�b�v����----------------------------------------------------
	if (this->_state == HoldState::Non) {
		JudgeResult result;
		//�ʂ�߂������̔���(Miss)
		if (this->_perfectTiming - Counter::_gameCnt <= -judgetime) { 
			this->_state = HoldState::Hold;
			return JudgeResult::Miss;
		}
		if (KeyBoard::KeyDown(Object::lane->GetKeyCode(this->_lane))) {
			//�܂����胉�C���ɓ��B���Ă��Ȃ��āA���莞�Ԃ͈̔͂ɓ����Ă��Ȃ��Ȃ�
			if (this->_perfectTiming - Counter::_gameCnt > judgetime) return JudgeResult::Non;
			//����͈͂ɓ����Ă���Ȃ�
			else if (this->_perfectTiming - Counter::_gameCnt > judgetime) result = JudgeResult::Miss;//X�b�ȏシ���Ă�����Miss
			else if (this->_perfectTiming - Counter::_gameCnt > judgetime - 3) result = JudgeResult::Good;//��L�ȓ���X�b�ȏシ���Ă�����Good
			else if (this->_perfectTiming - Counter::_gameCnt > judgetime - 5) result = JudgeResult::Great;//��L�ȓ���X�b�ȏシ���Ă�����Great
			else result = JudgeResult::Perfect;//�ǂ�ɂ����Ă͂܂�Ȃ��Ȃ�Perfect
			this->_state = HoldState::Hold;
			return result;
		}
	}
	//�z�[���h����------------------------------------------------------
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
