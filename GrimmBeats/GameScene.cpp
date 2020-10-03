#include "GameScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"Time.h"
#include"NotesCreater.h"
#include"MemoryFunc.h"
#include"SceneManager.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"
#include"Lane.h"
#include"JudgeLine.h"
#include"JudgeButton.h"
#include"JudgeResultLabel.h"
#include"ClearGauge.h"
#include"ScoreLabel.h"
#include"NotesController.h"
#include"ComboLabel.h"
#include "MusicDataManager.h"

#pragma region �J�E���^�[
float Counter::_gameCnt;
int Counter::_perfectCnt;
int Counter::_greatCnt;
int Counter::_goodCnt;
int Counter::_missCnt;
int Counter::_score;
int Counter::_comboCnt;
#pragma endregion

GameScene::GameScene()
{
	this->_isStart = false;
}

void GameScene::Initialize()
{
	GraphicResource::Load("game");
	Audio::Load("game");

	#pragma region �l�̏�����
	this->_isStart = false;
	this->_move_background = true;
	this->_background_graph = GraphicResource::GetHandle("AirBack")[0];
	this->graph_Xsize = ScreenData::width * 2;
	//�w�i�摜�̏����l�Z�b�g
	this->_bgPosition["bg1"] = Point(0, 0);
	this->_bgPosition["bg2"] = Point(this->graph_Xsize, 0);
	//�J�E���^�[
	Counter::_gameCnt = 0;
	Counter::_perfectCnt = 0;
	Counter::_greatCnt = 0;
	Counter::_goodCnt = 0;
	Counter::_missCnt = 0;
	Counter::_score = 0;
	Counter::_comboCnt = 0;
	//��Փx(�y�ȑI����ʂŌ��߂�)
	SelectMusic::level = Level::hard;
	#pragma endregion

	#pragma region �I�u�W�F�N�g�̏�����
	sceneManager->AddActor(new Lane());
	sceneManager->AddActor(new JudgeLine());
	sceneManager->AddActor(new JudgeResultLabel());
	sceneManager->AddActor(new ClearGauge());
	sceneManager->AddActor(new NotesController());
	sceneManager->AddActor(new ScoreLabel());
	sceneManager->AddActor(new ComboLabel());
	sceneManager->AddActor(new JudgeButton());

	NotesCreater::Initialize();
	#pragma endregion
}

void GameScene::Finalize()
{
	this->_bgPosition.clear();
	NotesCreater::Finalize();

	sceneManager->KillActorALL();

	Necessary::DeleteMusicListItem();
	
	Time::DeleteTimer("StartGame");
	Audio::DeleteSoundDataScope("game");
	GraphicResource::DeleteGraphScope("game");
}

void GameScene::Update()
{
	//�������H(Guide���邩��)
	if (KeyBoard::KeyDown(KEY_INPUT_RETURN) && this->_isStart == false) {
		Time::CreateTimer("StartGame");
		Audio::Play(MusicDataManager::GetInfo(SelectMusic::Name).musicName, false);
		this->_isStart = true;
	}
	Counter::_gameCnt = Time::GetElapsedTime("StartGame", Time::TimeFormat::Fream);
	//------------------------------------------------------------------------------
	sceneManager->ChangeScene(this->_isStart && Audio::CheckPlayScope("game") == false, SceneKind::MusicSelect);
}

void GameScene::Draw()
{
	this->DrawMoveBG();
}
