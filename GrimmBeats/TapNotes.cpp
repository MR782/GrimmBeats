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
	else if (abs(this->_perfectTiming - 9) > 5) return JudgeResult::Miss;//X�b�ȏシ���Ă�����Miss
	else if (abs(this->_perfectTiming - 9) > 4) return JudgeResult::Good;//��L�ȓ���X�b�ȏシ���Ă�����Good
	else if (abs(this->_perfectTiming - 9) > 3) return JudgeResult::Great;//��L�ȓ���X�b�ȏシ���Ă�����Great
	return JudgeResult::Perfect;//�ǂ�ɂ����Ă͂܂�Ȃ��Ȃ�Perfect
}

