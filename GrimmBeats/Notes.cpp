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
	//�I�_�̈ʒu + �I�_����n�_�ւ̕��� * ((���胉�C���ɂ��鎞�� - �Ȃ̍Đ�����)*���[���̒���*�X�s�[�h);                                    
	//float posY = Model::judge_line->get_position().y + ((this->_perfectTiming - Counter::_gameCnt)
	//	* -(Model::judge_line->get_position().y) * (0.001f * Necessary::speed));
	//this->_position.y = posY;
}
