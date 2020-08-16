#include "JudgeLine.h"


JudgeLine::~JudgeLine()
{
}

void JudgeLine::Initialize()
{
	this->anim = std::make_unique<Animation>();
	this->anim->set("");

	this->_blink = false;
	this->_position = Vector2();
}

void JudgeLine::Finalize()
{
}

void JudgeLine::Update()
{
}
