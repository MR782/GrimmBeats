#include "Scene.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

void Scene::Initialize()
{
	//背景画像の初期値セット
	this->_bgPosition["bg1"] = Point(0,0);
	this->_bgPosition["bg2"] = Point(ScreenData::width,0);
	//その他初期化
	this->_move_background = false;
	this->_background_graph = 0;
}

void Scene::Draw()
{
	this->DrawBG();
}

void Scene::DrawBG()
{
	//背景画像を移動するようにしたなら
	if (this->_move_background) {
		//移動処理と2枚目の背景を描画する
		#pragma region 背景移動(X移動処理)
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
