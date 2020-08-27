#include "TitleScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"SceneManager.h"
#include"KeyBoard.h"
#include"MemoryFunc.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"

TitleScene::TitleScene()
{
	this->_titleGuide = nullptr;
	this->_titleLogo = nullptr;
}

void TitleScene::Initialize()
{
	//リソースのロード
	MovieResource::Load("title");
	Audio::Load("title");
	Audio::Play("TitleBGM", true);
	//初期化
	#pragma region 背景の初期化
	this->_move_background = false;
	this->_background_graph = GraphicResource::GetHandle("TitleBack")[0];
	//ムービーの初期化
	this->_movie = std::make_unique<Movie>();
	this->_movie->Set("Leaf");
	this->graph_Xsize = ScreenData::width;//背景画像の大きさをセット
#pragma endregion

	#pragma region オブジェクトの初期化
	//ガイドレベルの初期化
	this->_titleGuide = new TitleGuide();
	this->_titleLogo = new TitleLogo();
	MemoryFunction::CheckMem(this->_titleLogo);
	MemoryFunction::CheckMem(this->_titleGuide);
	this->_titleGuide->Initialize();
	this->_titleLogo->Initialize();
	#pragma endregion

	//初期値セット
	this->_bgPosition["bg1"] = Point(0, 0);
	this->decisionSEName = "decision_Title";
	this->nextScene = SceneKind::ModeSelect;
}

void TitleScene::Finalize()
{
	this->_movie->Delete();
	this->_movie.reset();
	Audio::DeleteSoundDataScope("title");
	this->_titleGuide->Finalize();
	this->_titleLogo->Finalize();

	delete this->_titleLogo;
	delete this->_titleGuide;
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

	//オブジェクト描画
	this->_titleLogo->Draw();
	this->_titleGuide->Draw();
}
