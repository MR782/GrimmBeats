#include "GameScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"MemoryFunc.h"

float Counter::_gameCnt;

Lane* Object::lane;
JudgeLine* Object::judgeLine;

void GameScene::Initialize()
{
	#pragma region オブジェクトの初期化
	Object::lane = new Lane();
	Object::judgeLine = new JudgeLine();
	this->_judgeButoon = new JudgeButton();

	MemoryFunction::CheckMem(Object::lane);
	MemoryFunction::CheckMem(Object::judgeLine);
	MemoryFunction::CheckMem(this->_judgeButoon);

	Object::lane->Initialize();
	Object::judgeLine->Initialize();
	this->_judgeButoon->Initialize();
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
	Object::judgeLine->Finalize();
	this->_judgeButoon->Finalize();

	delete Object::lane;
	delete Object::judgeLine;
	delete this->_judgeButoon;
}

void GameScene::Update()
{
	this->_judgeButoon->Update();
}

void GameScene::Draw()
{
	this->DrawMoveBG();

	Object::lane->Draw();
	Object::judgeLine->Draw();

	this->_judgeButoon->Draw();
}
