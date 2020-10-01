#include "HoldNotes.h"
#include"KeyBoard.h"
#include"GameScene.h"
#include"SceneManager.h"
#include"./dxlib/DxLib.h"

void HoldNotes::Move()
{
	Vector2 linePos = sceneManager->FindActor("JudgeLine")->GetPosition();
	//�n�_�ƏI�_�ŕ`����Ǘ����邽��Start��End�����ړ�������
	float startPosY = linePos.y + ((this->_perfectTiming - Counter::_gameCnt)
		* -(linePos.y) * (0.001f * (float)Necessary::speed));

	this->_drawRect.y = (int)startPosY;

	float endPosY = linePos.y + ((this->_holdTime - Counter::_gameCnt)
		* -(linePos.y) * (0.001f * (float)Necessary::speed));

	this->_drawRect.h = (int)endPosY;
}

HoldNotes::HoldNotes()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("HoldNotes");
	this->_state = HoldState::Non;
	this->_holdCnt = 0;
}

JudgeResult HoldNotes::Judge()
{
	if (this->_holdTime <= Counter::_gameCnt) {
		this->_judgeFinish = true;
	}
	int keycode = Lane::GetKeyCode(this->_lane);
	if (KeyBoard::KeyPress(keycode)) {
		//�I�_�̎��Ԃɂ͓��B���Ă��炸,
		//�擪�̃^�C�~���O���߂��Ă���Ȃ�
		if (this->_perfectTiming <= Counter::_gameCnt
			&&
			this->_holdTime >= Counter::_gameCnt) {
			this->_holdCnt++;
			if (this->_holdCnt % 5 == 0) return JudgeResult::Perfect;
			else JudgeResult::HoldNow;
		}
	}
	else {
		if (this->_perfectTiming <= Counter::_gameCnt
			&&
			this->_holdTime >= Counter::_gameCnt) {
			this->_holdCnt++;
			if (this->_holdCnt % 5 == 0) return JudgeResult::Miss;
			else JudgeResult::HoldNow;
		}
	}
	return JudgeResult::Non;
}

void HoldNotes::SetInfo(float p_timing, LaneName lane, float endtime)
{
	float notesHeight = 16;
	this->_perfectTiming = p_timing;
	this->_lane = lane;
	this->_holdTime = endtime;
	this->_judgeFinish = false;
	//�I�_�Ǝn�_�ŋ�`�����
	Rect laneRect = Lane::GetLaneRect(lane);
	Vector2 judgeLinePos = sceneManager->FindActor("JudgeLine")->GetPosition();

	Rect draw = Rect(laneRect.x + 1,//X
		(int)(judgeLinePos.y + ((this->_perfectTiming - Counter::_gameCnt) * -(judgeLinePos.y) * (0.001f * (float)Necessary::speed))),//Y
		laneRect.x + laneRect.w,
		(int)(judgeLinePos.y + ((this->_holdTime - Counter::_gameCnt) * -(judgeLinePos.y) * (0.001f * (float)Necessary::speed))));//W,H
	this->_drawRect = draw;
}

void HoldNotes::Draw()
{
	this->_anim->ExtendRectDraw(this->_drawRect);
}
