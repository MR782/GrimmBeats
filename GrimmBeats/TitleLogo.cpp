#include "TitleLogo.h"

void TitleLogo::Initialize()
{
	this->_position = Vector2();
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("TitleLogo");
}

void TitleLogo::Finalize()
{
}

void TitleLogo::Update()
{
}

void TitleLogo::Draw()
{
	this->_anim->ExtendAnimeDraw(Rect());
}
