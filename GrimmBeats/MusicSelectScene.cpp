#include "MusicSelectScene.h"
#include"MusicDataManager.h"
#include"GraphicResource.h"
#include"MemoryFunc.h"
#include"ScreenSystem.h"
#include"Audio.h"

std::string MusicName::musicName;
MusicListItemButton* UIModel::musicItemList;


MusicSelectScene::MusicSelectScene()
{
	UIModel::musicItemList = nullptr;
	this->bpmLabel = nullptr;
	this->composerLabel = nullptr;
	this->musicNameLabel = nullptr;
	this->cursor = nullptr;
	this->uiBoard = nullptr;
	this->speedLabel = nullptr;
}

void MusicSelectScene::Initialize()
{
	Audio::Load("game");

	#pragma region UIオブジェクトの生成と初期化
	this->bpmLabel = new BPMLabel();
	this->composerLabel = new ComposerLabel();
	this->musicNameLabel = new MusicNameLabel();
	this->cursor = new MusicSelectCursor();
	this->speedLabel = new SpeedLabel();
	UIModel::musicItemList = new MusicListItemButton();

	MemoryFunction::CheckMem(UIModel::musicItemList);
	MemoryFunction::CheckMem(this->bpmLabel);
	MemoryFunction::CheckMem(this->composerLabel);
	MemoryFunction::CheckMem(this->musicNameLabel);
	MemoryFunction::CheckMem(this->cursor);
	MemoryFunction::CheckMem(this->speedLabel);

	this->bpmLabel->Initialize();
	this->composerLabel->Initialize();
	this->musicNameLabel->Initialize();
	this->cursor->Initialize();
	this->speedLabel->Initialize();
	UIModel::musicItemList->Initialize();
	#pragma endregion

	this->nextScene = SceneKind::Game;
	this->_background_graph = GraphicResource::GetHandle("MusicSelectBack")[0];
	this->uiBoard = std::make_unique<Animation>();
	this->uiBoard->Set("UIBoard");
	MusicName::musicName = "Air";

	Audio::Play(MusicDataManager::GetInfo(MusicName::musicName).demomusicName, false);
}

void MusicSelectScene::Finalize()
{
	this->composerLabel->Finalize();
	this->bpmLabel->Finalize();
	this->musicNameLabel->Finalize();
	this->cursor->Finalize();
	this->speedLabel->Finalize();
	UIModel::musicItemList->Finalize();

	delete UIModel::musicItemList;
	delete this->musicNameLabel;
	delete this->composerLabel;
	delete this->bpmLabel;
	delete this->cursor;
}

void MusicSelectScene::Update()
{
	this->cursor->Update();
	this->speedLabel->Update();
}

void MusicSelectScene::Draw()
{
	this->DrawBG();
	//映像描画
	this->uiBoard->ExtendAnimeDraw(Rect(0,0,ScreenData::width / 2,ScreenData::height / 2));
	this->musicNameLabel->Draw();
	this->bpmLabel->Draw();
	this->composerLabel->Draw();
	this->cursor->Draw();
	UIModel::musicItemList->Draw();
	this->speedLabel->Draw();
}
