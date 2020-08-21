#include "GameScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"

void GameScene::Initialize()
{
	this->_move_background = true;
	this->_background_graph = GraphicResource::GetHandle("AirBack")[0];
	this->graph_Xsize = ScreenData::width * 2;
	//”wŒi‰æ‘œ‚Ì‰Šú’lƒZƒbƒg
	this->_bgPosition["bg1"] = Point(0, 0);
	this->_bgPosition["bg2"] = Point(this->graph_Xsize, 0);
}

void GameScene::Finalize()
{
}

void GameScene::Update()
{
}
