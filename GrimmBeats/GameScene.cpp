#include "GameScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"Time.h"
#include"NotesCreater.h"
#include"MemoryFunc.h"
#include"SceneManager.h"

#pragma region カウンター
float Counter::_gameCnt;
int Counter::_perfectCnt;
int Counter::_greatCnt;
int Counter::_goodCnt;
int Counter::_missCnt;
int Counter::_score;
#pragma endregion

#pragma region オブジェクト
Lane* Object::lane;
JudgeLine* Object::judgeLine;
JudgeResultLabel* Object::judgeResultLabel;
#pragma endregion

void GameScene::Initialize()
{
	GraphicResource::Load("game");
	GraphicResource::Load("uiboard");

	#pragma region 値の初期化
	this->_move_background = true;
	this->_background_graph = GraphicResource::GetHandle("AirBack")[0];
	this->graph_Xsize = ScreenData::width * 2;
	//背景画像の初期値セット
	this->_bgPosition["bg1"] = Point(0, 0);
	this->_bgPosition["bg2"] = Point(this->graph_Xsize, 0);
	//カウンター
	Counter::_gameCnt = 0;
	Counter::_perfectCnt = 0;
	Counter::_greatCnt = 0;
	Counter::_goodCnt = 0;
	Counter::_missCnt = 0;
	Counter::_score = 0;
	//難易度(楽曲選択画面で決める)
	SelectMusic::level = Level::hard;
	#pragma endregion

	#pragma region オブジェクトの初期化
	Object::lane = new Lane();
	Object::judgeLine = new JudgeLine();
	Object::judgeResultLabel = new JudgeResultLabel();
	this->_judgeButton = new JudgeButton();
	this->_scoreLabel = new ScoreLabel();
	this->_clearGauge = new ClearGauge();
	this->_notesController = new NotesController;

	MemoryFunction::CheckMem(Object::lane);
	MemoryFunction::CheckMem(Object::judgeLine);
	MemoryFunction::CheckMem(Object::judgeResultLabel);
	MemoryFunction::CheckMem(this->_judgeButton);
	MemoryFunction::CheckMem(this->_scoreLabel);
	MemoryFunction::CheckMem(this->_clearGauge);
	MemoryFunction::CheckMem(this->_notesController);

	Object::lane->Initialize();
	Object::judgeLine->Initialize();
	Object::judgeResultLabel->Initialize();
	this->_judgeButton->Initialize();
	this->_scoreLabel->Initialize();
	this->_clearGauge->Initialize();
	NotesCreater::Initialize();
	this->_notesController->Initialize();
	#pragma endregion
}

void GameScene::Finalize()
{
	Object::lane->Finalize();
	Object::judgeLine->Finalize();
	Object::judgeResultLabel->Finalize();
	this->_judgeButton->Finalize();
	this->_scoreLabel->Finalize();
	this->_clearGauge->Finalize();
	this->_notesController->Finalize();
	NotesCreater::Finalize();

	delete Object::lane;
	delete Object::judgeLine;
	delete Object::judgeResultLabel;
	delete this->_judgeButton;
	delete this->_scoreLabel;
	delete this->_clearGauge;
	delete this->_notesController;

	GraphicResource::DeleteGraphScope("game");
	GraphicResource::DeleteGraphScope("uiboard");
}

void GameScene::Update()
{
	this->_judgeButton->Update();
	this->_clearGauge->Update();
	this->_notesController->Update();
}

void GameScene::Draw()
{
	this->DrawMoveBG();

	Object::lane->Draw();
	Object::judgeLine->Draw();
	Object::judgeResultLabel->Draw();
	this->_scoreLabel->Draw();
	this->_judgeButton->Draw();
	this->_clearGauge->Draw();
	this->_notesController->Draw();
}
