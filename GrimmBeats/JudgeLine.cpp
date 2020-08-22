#include "JudgeLine.h"


JudgeLine::~JudgeLine()
{
}

void JudgeLine::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("");
	this->_position = Vector2();
}

void JudgeLine::Finalize()
{
}

void JudgeLine::Update()
{
}
