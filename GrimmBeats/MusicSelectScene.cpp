#include "MusicSelectScene.h"
#include"MusicDataManager.h"
#include"GraphicResource.h"
#include"MemoryFunc.h"
#include"SceneManager.h"
#include"ScreenSystem.h"
#include"KeyBoard.h"
#include"ScreenFunction.h"
#include"Audio.h"

MusicSelectScene::MusicSelectScene()
{
}

void MusicSelectScene::Initialize()
{
	Audio::Load("musicselect");
	GraphicResource::Load("musicselect");

	#pragma region UIオブジェクトの生成と初期化
	sceneManager->AddActor(new BPMLabel());
	sceneManager->AddActor(new MusicNameLabel());
	sceneManager->AddActor(new MusicSelectCursor());
	sceneManager->AddActor(new ComposerLabel());
	sceneManager->AddActor(new SpeedLabel());
	sceneManager->AddActor(new MusicListItemButton());
	#pragma endregion

	#pragma region 値の初期化
	this->nextScene = SceneKind::Game;
	this->_background_graph = GraphicResource::GetHandle("MusicSelectBack")[0];
	this->_uiBoard = std::make_unique<Animation>();
	this->_uiBoard->Set("UIBoard");
	SelectMusic::Name = "Air";
	Necessary::speed = 1;
	this->decisionSEName = "decision_MusicSelect";
	#pragma endregion 

	Audio::Play(MusicDataManager::GetInfo(SelectMusic::Name).demomusicName, false);
}

void MusicSelectScene::Finalize()
{
	this->_uiBoard.reset();

	sceneManager->KillActorALL();

	Audio::DeleteSoundDataScope("musicselect");
	GraphicResource::DeleteGraphScope("musicselect");
}

void MusicSelectScene::Update()
{
	//------------------------------------------------------------------------------
	sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), this->nextScene);
}

void MusicSelectScene::Draw()
{
	this->DrawBG();

	this->_uiBoard->ExtendAnimeDraw(Rect(0,0,ScreenData::width / 2,ScreenData::height / 2));
}
