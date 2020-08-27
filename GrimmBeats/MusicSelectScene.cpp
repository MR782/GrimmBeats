#include "MusicSelectScene.h"
#include"MusicDataManager.h"
#include"GraphicResource.h"
#include"MemoryFunc.h"
#include"SceneManager.h"
#include"ScreenSystem.h"
#include"KeyBoard.h"
#include"ScreenFunction.h"
#include"Audio.h"

MusicListItemButton* UIModel::musicItemList;

MusicSelectScene::MusicSelectScene()
{
	UIModel::musicItemList = nullptr;
	this->_bpmLabel = nullptr;
	this->_composerLabel = nullptr;
	this->_musicNameLabel = nullptr;
	this->_cursor = nullptr;
	this->_uiBoard = nullptr;
	this->_speedLabel = nullptr;
}

void MusicSelectScene::Initialize()
{
	Audio::Load("musicselect");
	Audio::SetVolumeAudioName("Air_DEMO", 75);
	Audio::SetVolumeAudioName("PROVIDENCE-CORE_DEMO", 75);

	#pragma region UIオブジェクトの生成と初期化
	this->_bpmLabel = new BPMLabel();
	this->_composerLabel = new ComposerLabel();
	this->_musicNameLabel = new MusicNameLabel();
	this->_cursor = new MusicSelectCursor();
	this->_speedLabel = new SpeedLabel();
	UIModel::musicItemList = new MusicListItemButton();

	MemoryFunction::CheckMem(UIModel::musicItemList);
	MemoryFunction::CheckMem(this->_bpmLabel);
	MemoryFunction::CheckMem(this->_composerLabel);
	MemoryFunction::CheckMem(this->_musicNameLabel);
	MemoryFunction::CheckMem(this->_cursor);
	MemoryFunction::CheckMem(this->_speedLabel);

	this->_bpmLabel->Initialize();
	this->_composerLabel->Initialize();
	this->_musicNameLabel->Initialize();
	this->_cursor->Initialize();
	this->_speedLabel->Initialize();
	UIModel::musicItemList->Initialize();
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
	this->_composerLabel->Finalize();
	this->_bpmLabel->Finalize();
	this->_musicNameLabel->Finalize();
	this->_cursor->Finalize();
	this->_speedLabel->Finalize();
	UIModel::musicItemList->Finalize();

	delete UIModel::musicItemList;
	delete this->_musicNameLabel;
	delete this->_composerLabel;
	delete this->_bpmLabel;
	delete this->_cursor;

	Audio::DeleteSoundDataScope("musicselect");
	Audio::StopAll();
}

void MusicSelectScene::Update()
{
	if (ScreenFunction::CheckBlendMin()) {
		this->_cursor->Update();
		this->_speedLabel->Update();
	}
	//------------------------------------------------------------------------------
	sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), this->nextScene);
}

void MusicSelectScene::Draw()
{
	this->DrawBG();
	//映像描画
	this->_uiBoard->ExtendAnimeDraw(Rect(0,0,ScreenData::width / 2,ScreenData::height / 2));
	this->_musicNameLabel->Draw();
	this->_bpmLabel->Draw();
	this->_composerLabel->Draw();
	this->_cursor->Draw();
	UIModel::musicItemList->Draw();
	this->_speedLabel->Draw();
}
