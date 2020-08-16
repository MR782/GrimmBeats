#include "Scene.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

void Scene::Initialize()
{
	//”wŒi‰æ‘œ‚Ì‰Šú’lƒZƒbƒg
	this->_bgPosition["bg1"] = Point(0,0);
	this->_bgPosition["bg2"] = Point(ScreenData::width,0);
	//‚»‚Ì‘¼‰Šú‰»
	this->_move_background = false;
	this->_background_graph = 0;
}

void Scene::Draw()
{
	this->DrawBG();
}

void Scene::DrawBG()
{
	//”wŒi‰æ‘œ‚ðˆÚ“®‚·‚é‚æ‚¤‚É‚µ‚½‚È‚ç
	if (this->_move_background) {
		//ˆÚ“®ˆ—‚Æ2–‡–Ú‚Ì”wŒi‚ð•`‰æ‚·‚é
		#pragma region ”wŒiˆÚ“®(XˆÚ“®ˆ—)
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
