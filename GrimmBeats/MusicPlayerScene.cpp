#include "MusicPlayerScene.h"
#include"Audio.h"
#include"MemoryFunc.h"
#include"SceneManager.h"
#include"MusicDataManager.h"
#include"ScreenFunction.h"
#include"KeyBoard.h"
#include"ScreenSystem.h"
#include"./dxlib/DxLib.h"

MusicPlayerScene::MusicPlayerScene()
{
	this->_uiBoard = nullptr;
}

void MusicPlayerScene::Initialize()
{
	Audio::Load("game");
	Audio::Load("system");
	GraphicResource::Load("musicselect");

	#pragma region UIオブジェクトの生成と初期化

	#pragma endregion

	#pragma region 値の初期化
	this->nextScene = SceneKind::ModeSelect;
	this->_background_graph = GraphicResource::GetHandle("MusicSelectBack")[0];
	this->_uiBoard = std::make_unique<Animation>();
	this->_uiBoard->Set("UIBoard");
	SelectMusic::Name = "Air";
	this->decisionSEName = "decision_MusicSelect";
	#pragma endregion 

	Audio::Play(MusicDataManager::GetInfo(SelectMusic::Name).musicName, false);
}

void MusicPlayerScene::Finalize()
{
	this->_uiBoard.reset();

	Audio::DeleteSoundDataScope("game");
	Audio::DeleteSoundDataScope("system");
	GraphicResource::DeleteGraphScope("musicselect");
}

void MusicPlayerScene::Update()
{
	if (ScreenFunction::CheckBlendMin()) {
		
	}
	//------------------------------------------------------------------------------
	sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_BACK), this->nextScene);
}

void MusicPlayerScene::Draw()
{
	this->DrawBG();
	//映像描画
	this->_uiBoard->ExtendAnimeDraw(Rect(0, 0, ScreenData::width / 2, ScreenData::height / 2));
}
