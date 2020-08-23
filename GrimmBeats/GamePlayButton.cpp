#include "GamePlayButton.h"
#include"ScreenSystem.h"

void GamePlayerButton::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("GamePlayButton");

	this->_position = Vector2();
	this->_drawRect = Rect(ScreenData::width / 4, ScreenData::height / 5, ScreenData::width / 2, ScreenData::height / 4);
}

void GamePlayerButton::Finalize()
{
	this->_anim.reset();
}

void GamePlayerButton::Update()
{
}

void GamePlayerButton::Draw()
{
	this->_anim->ExtendAnimeDraw(this->_drawRect);
}

Rect GamePlayerButton::GetDrawRect()
{
	return this->_drawRect;
}
