#include "GameScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"MemoryFunc.h"

float Counter::_gameCnt;
Lane* Object::lane;

void GameScene::Initialize()
{
	#pragma region オブジェクトの初期化
	Object::lane = new Lane();

	MemoryFunction::CheckMem(Object::lane);

	Object::lane->Initialize();
	#pragma endregion

	#pragma region 値の初期化
	this->_move_background = true;
	this->_background_graph = GraphicResource::GetHandle("AirBack")[0];
	this->graph_Xsize = ScreenData::width * 2;
	//背景画像の初期値セット
	this->_bgPosition["bg1"] = Point(0, 0);
	this->_bgPosition["bg2"] = Point(this->graph_Xsize, 0);
	#pragma endregion
}

void GameScene::Finalize()
{
	Object::lane->Finalize();

	delete Object::lane;
}

void GameScene::Update()
{
}

void GameScene::Draw()
{
	this->DrawMoveBG();

	Object::lane->Draw();
}
