#include "TitleLogo.h"
#include"ScreenSystem.h"

void TitleLogo::Initialize()
{
	this->_position = Vector2();
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("TitleLogo");
}

void TitleLogo::Finalize()
{
	this->_anim.reset();
}

void TitleLogo::Update()
{
}

void TitleLogo::Draw()
{
	this->_anim->ExtendAnimeDraw(Rect(0, 0, ScreenData::width, ScreenData::height));
}
