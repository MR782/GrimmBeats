#include "MusicPlayerButton.h"
#include"ScreenSystem.h"

void MusicPlayerButton::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("MusicPlayerButton");

	this->name = "MusicPlayerButton";
	this->_position = Vector2();
	this->_drawRect = Rect(ScreenData::width / 4,( ScreenData::height / 5) * 3, ScreenData::width / 2, ScreenData::height / 4);
}

void MusicPlayerButton::Finalize()
{
	this->_anim.reset();
}

void MusicPlayerButton::Update()
{
}

void MusicPlayerButton::Draw()
{
	this->_anim->ExtendAnimeDraw(this->_drawRect);
}
