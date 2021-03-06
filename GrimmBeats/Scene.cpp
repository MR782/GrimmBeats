#include "Scene.h"
#include"MemoryFunc.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"


Scene::Scene()
{
	this->_background_graph = 0;
	this->_move_background = false;
	this->graph_Xsize = 0;
	this->decisionSEName = "";
	this->nextScene = SceneKind::Title;
}

void Scene::Initialize()
{
	//背景画像の初期値セット
	this->_bgPosition["bg1"] = Point(0, 0);
	this->_bgPosition["bg2"] = Point(this->graph_Xsize, 0);
	//その他初期化
	this->_move_background = false;
	this->_background_graph = 0;
}

void Scene::Draw()
{
	if (this->_move_background) {
		DrawMoveBG();
		return;
	}
	this->DrawBG();
}

std::string Scene::GetDecisionSEName()
{
	return this->decisionSEName;
}

void Scene::DrawBG()
{
	DrawExtendGraph(0, 0,
		ScreenData::width, ScreenData::height,
		this->_background_graph, FALSE);
}

void Scene::DrawMoveBG()
{
	//移動処理と2枚目の背景を描画する
#pragma region 背景移動(X移動処理)
	this->_bgPosition["bg1"].x -= 1;
	this->_bgPosition["bg2"].x -= 1;
	if (this->_bgPosition["bg1"].x < -this->graph_Xsize) this->_bgPosition["bg1"].x = this->graph_Xsize - 1;
	if (this->_bgPosition["bg2"].x < -this->graph_Xsize) this->_bgPosition["bg2"].x = this->graph_Xsize - 1;
#pragma endregion

	DrawExtendGraph(this->_bgPosition["bg2"].x, this->_bgPosition["bg2"].y,
		this->graph_Xsize + this->_bgPosition["bg2"].x, ScreenData::height,
		this->_background_graph, FALSE);

	DrawExtendGraph(this->_bgPosition["bg1"].x, this->_bgPosition["bg1"].y,
		this->graph_Xsize + this->_bgPosition["bg1"].x, ScreenData::height,
		this->_background_graph, FALSE);
}