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

	//���胉�C���ɓ��B���Ă���7�t���[���ȏソ������Miss����(�L�[��������Ă��Ȃ��Ă�)
	if (this->_perfectTiming - Counter::_gameCnt <= -judgetime) return JudgeResult::Miss;

	//�L�[�������ꂽ�ꍇ�̔���----------------------------------------------------------------------------
	if (!KeyBoard::KeyDown(Object::lane->GetKeyCode(this->_lane))) return JudgeResult::Non;
	JudgeResult result;
	//�܂����胉�C���ɓ��B���Ă��Ȃ��āA���莞�Ԃ͈̔͂ɓ����Ă��Ȃ��Ȃ�
	if (this->_perfectTiming - Counter::_gameCnt > judgetime) return JudgeResult::Non;
	//����͈͂ɓ����Ă���Ȃ�
	else if (abs(this->_perfectTiming - Counter::_gameCnt) > judgetime) result = JudgeResult::Miss;//X�b�ȏシ���Ă�����Miss
	else if (abs(this->_perfectTiming - Counter::_gameCnt) > judgetime - 3) result = JudgeResult::Good;//��L�ȓ���X�b�ȏシ���Ă�����Good
	else if (abs(this->_perfectTiming - Counter::_gameCnt) > judgetime - 5) result = JudgeResult::Great;//��L�ȓ���X�b�ȏシ���Ă�����Great
	else result = JudgeResult::Perfect;//�ǂ�ɂ����Ă͂܂�Ȃ��Ȃ�Perfect
	this->_judgeFinish = true;
	return result;
}

