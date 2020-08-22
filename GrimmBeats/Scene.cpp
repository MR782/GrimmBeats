#include "Scene.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

Scene::Scene()
{
	this->_background_graph = 0;
	this->_move_background = false;
	this->graph_Xsize = 0;
}

void Scene::Initialize()
{
	//”wŒi‰æ‘œ‚Ì‰Šú’lƒZƒbƒg
	this->_bgPosition["bg1"] = Point(0, 0);
	this->_bgPosition["bg2"] = Point(this->graph_Xsize, 0);
	//‚»‚Ì‘¼‰Šú‰»
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

void Scene::DrawBG()
{
	DrawExtendGraph(0, 0,
		ScreenData::width, ScreenData::height,
		this->_background_graph, FALSE);
}

void Scene::DrawMoveBG()
{
	//ˆÚ“®ˆ—‚Æ2–‡–Ú‚Ì”wŒi‚ð•`‰æ‚·‚é
	#pragma region ”wŒiˆÚ“®(XˆÚ“®ˆ—)
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
