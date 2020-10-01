#include "TitleGuide.h"
#include"ScreenSystem.h"
#include<math.h>
#include"dxlib/DxLib.h"

void TitleGuide::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("TitleGuide");
	this->_position = Vector2();
	this->name = "TitleGuide";
}

void TitleGuide::Finalize()
{
	this->_anim.reset();
}

void TitleGuide::Update()
{
}

void TitleGuide::Draw()
{
	Rect drawrect = Rect(ScreenData::width / 4, (ScreenData::height / 8) * 5,
		ScreenData::width / 2, ScreenData::height / 5);

	this->_anim->BlinkExtendDraw(200, 240, drawrect);
}
