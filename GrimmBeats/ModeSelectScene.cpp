#include "ModeSelectScene.h"
#include"GraphicResource.h"
#include"Audio.h"
#include"ScreenFunction.h"
#include"KeyBoard.h"
#include"SceneManager.h"
#include"./dxlib/DxLib.h"

ModeSelectCursor* ModeSelectUI::cursol;
GamePlayerButton* ModeSelectUI::gameplay_button;
MusicPlayerButton* ModeSelectUI::musicplay_button;

void ModeSelectScene::Initialize()
{
	//リソースのロード
	Audio::Load("modeselect");
	Audio::Play("ModeSelectBGM", true);

	#pragma region 値の初期化
	this->_bgPosition.clear();
	this->graph_Xsize = 0;
	this->_background_graph = GraphicResource::GetHandle("ModeSelectBack")[0];
	this->_move_background = false;
	this->decisionSEName = "decision_ModeSelect";
	#pragma endregion

	#pragma region オブジェクトの初期化
	ModeSelectUI::cursol = new ModeSelectCursor();
	ModeSelectUI::gameplay_button = new GamePlayerButton();
	ModeSelectUI::musicplay_button = new MusicPlayerButton();

	ModeSelectUI::cursol->Initialize();
	ModeSelectUI::gameplay_button->Initialize();
	ModeSelectUI::musicplay_button->Initialize();
	#pragma endregion
}

void ModeSelectScene::Finalize()
{
	this->_background_graph = 0;

	Audio::Stop("ModeSelectBGM");
	Audio::DeleteSoundDataScope("modeselect");

	ModeSelectUI::cursol->Finalize();
	ModeSelectUI::gameplay_button->Finalize();
	ModeSelectUI::musicplay_button->Finalize();

	delete ModeSelectUI::cursol;
	delete ModeSelectUI::gameplay_button;
	delete ModeSelectUI::musicplay_button;
}

void ModeSelectScene::Update()
{
	//フェードIOの最中でなければ
	if (ScreenFunction::CheckBlendMin()) {
		ModeSelectUI::cursol->Update();
	}
	
	#pragma region シーン遷移処理
	//シーン切り替え-----ENTERを押すとシーン遷移-----------------------------------
	switch (ModeSelectUI::cursol->GetNextScene())
	{
	case ModeSelectCursor::NextScene::MusicSelect:
		sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), SceneKind::Game);
		break;
	case ModeSelectCursor::NextScene::MusicPlayer:
		sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), SceneKind::MusicPlayer);
		break;
	default:
		throw("次のシーンが指定されていません");
	}
	#pragma endregion

}

void ModeSelectScene::Draw()
{
	this->DrawBG();
	ModeSelectUI::gameplay_button->Draw();
	ModeSelectUI::musicplay_button->Draw();
	ModeSelectUI::cursol->Draw();
}
