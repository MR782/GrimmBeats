#include "TitleScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"SceneManager.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"

TitleScene::TitleScene()
{
}

void TitleScene::Initialize()
{
	//リソースのロード
	MovieResource::Load("title");
	Audio::Load("title");
	Audio::Play("TitleBGM", true);
	GraphicResource::Load("title");
	//初期化
	#pragma region 背景の初期化
	this->_move_background = false;
	this->_background_graph = GraphicResource::GetHandle("TitleBack")[0];
	//ムービーの初期化
	this->_movie = std::make_unique<Movie>();
	this->_movie->Set("Leaf");
	this->graph_Xsize = ScreenData::width;//背景画像の大きさをセット
	#pragma endregion

	#pragma region オブジェクトの生成
	sceneManager->AddActor(new TitleGuide());
	sceneManager->AddActor(new TitleLogo());
	#pragma endregion

	//初期値セット
	this->_bgPosition["bg1"] = Point(0, 0);
	this->decisionSEName = "decision_Title";
	this->nextScene = SceneKind::ModeSelect;
}

void TitleScene::Finalize()
{
	GraphicResource::DeleteGraphScope("title");
	Audio::DeleteSoundDataScope("title");
	this->_movie->Delete();
	this->_movie.reset();

	sceneManager->KillActorALL();
}

void TitleScene::Update()
{
	//シーン切り替え-----ENTERを押すとシーン遷移-----------------------------------
	sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN),this->nextScene);
}

void TitleScene::Draw()
{
	//背景描画
	this->DrawBG();
	//映像描画
	this->_movie->Draw();
}
