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
	if (this->anim == nullptr) return;
	//オブジェクトを点滅させたいときに処理を行う
	if (this->_blink) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)sin(Time::now_time.QuadPart * 0.5f + 0.5f));
	}
	this->anim->draw_anime(this->_position);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);
}
