#include "GameObject.h"
#include"Time.h"
#include"MemoryFunc.h"
#include<math.h>
#include"dxlib/DxLib.h"

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	if (this->_anim == nullptr) return;
	this->_anim->DrawAnime(this->_position);
}

Vector2 GameObject::GetPosition()
{
	return this->_position;
}
