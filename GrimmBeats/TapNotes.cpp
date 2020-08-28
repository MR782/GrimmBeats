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
	else if (abs(this->_perfectTiming - 9) > 5) return JudgeResult::Miss;//X•bˆÈã‚·‚¬‚Ä‚¢‚½‚çMiss
	else if (abs(this->_perfectTiming - 9) > 4) return JudgeResult::Good;//ã‹LˆÈ“à‚ÅX•bˆÈã‚·‚¬‚Ä‚¢‚½‚çGood
	else if (abs(this->_perfectTiming - 9) > 3) return JudgeResult::Great;//ã‹LˆÈ“à‚ÅX•bˆÈã‚·‚¬‚Ä‚¢‚½‚çGreat
	return JudgeResult::Perfect;//‚Ç‚ê‚É‚à“–‚Ä‚Í‚Ü‚ç‚È‚¢‚È‚çPerfect
}

