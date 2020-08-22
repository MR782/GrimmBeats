#include "ModeSelectScene.h"
#include"GraphicResource.h"
#include"Audio.h"
#include"ScreenFunction.h"
#include"KeyBoard.h"
#include"SceneManager.h"
#include"./dxlib/DxLib.h"

void ModeSelectScene::Initialize()
{
	//リソースのロード
	Audio::Load("modeselect");
	Audio::Play("ModeSelectBGM", true);

	#pragma region 値の初期化
	this->_bgPosition.clear();
	this->graph_Xsize = 0;
	this->_background_graph = GraphicResource::GetHandle("")[0];
	this->_move_background = false;
	this->nextScene = NextScene::MusicSelect;
	#pragma endregion

	#pragma region オブジェクトの初期化
	
	#pragma endregion
}

void ModeSelectScene::Finalize()
{
	this->_background_graph = 0;
}

void ModeSelectScene::Update()
{
	//フェードIOの最中でなければ
	if (ScreenFunction::CheckBlendMin()) {

	}
	
	#pragma region シーン遷移処理
	//シーン切り替え-----ENTERを押すとシーン遷移-----------------------------------
	switch (this->nextScene)
	{
	case NextScene::MusicSelect:
		sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), SceneKind::MusicSelect);
		break;
	case NextScene::MusicPlayer:
		sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), SceneKind::MusicPlayer);
		break;
	default:
		throw("次のシーンが指定されていません");
	}
	#pragma endregion

}
