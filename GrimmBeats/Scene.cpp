#include "Scene.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

void Scene::Initialize()
{
	//�w�i�摜�̏����l�Z�b�g
	this->_bgPosition["bg1"] = Point(0,0);
	this->_bgPosition["bg2"] = Point(ScreenData::width,0);
	//���̑�������
	this->_move_background = false;
	this->_background_graph = 0;
}

void Scene::Draw()
{
	this->DrawBG();
}

void Scene::DrawBG()
{
	//�w�i�摜���ړ�����悤�ɂ����Ȃ�
	if (this->_move_background) {
		//�ړ�������2���ڂ̔w�i��`�悷��
		#pragma region �w�i�ړ�(X�ړ�����)
		this->_bgPosition["bg1"].x--;
		this->_bgPosition["bg2"].x--;
		if (this->_bgPosition["bg1"].x < -ScreenData::width) this->_bgPosition["bg1"].x = ScreenData::width;
		if (this->_bgPosition["bg2"].x < -ScreenData::width) this->_bgPosition["bg2"].x = ScreenData::width;
		#pragma endregion

		DrawExtendGraph(this->_bgPosition["bg2"].x, this->_bgPosition["bg2"].y,
			(ScreenData::width * 2) + this->_bgPosition["bg2"].x, ScreenData::height,
			this->_background_graph, FALSE);
	}
	DrawExtendGraph(this->_bgPosition["bg1"].x, this->_bgPosition["bg1"].y,
		ScreenData::width + this->_bgPosition["bg1"].x, ScreenData::height,
		this->_background_graph, FALSE);
	
}
