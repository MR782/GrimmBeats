#include "SceneManager.h"
#include"Necessary.h"
#include"ScreenFunction.h"
#include"MemoryFunc.h"
#include"Audio.h"

void SceneManager::Initialize()
{
	ScreenFunction::Initialize();

	this->nowScene = new TitleScene();//初期シーンの設定
	this->nowScene->Initialize();
}

void SceneManager::Finalize()
{
	this->nowScene->Finalize();

	ScreenFunction::Finalize();

	delete this->nowScene;
}

void SceneManager::Update()
{
	this->nowScene->Update();

	ScreenFunction::Update();
}

void SceneManager::Draw()
{
	this->nowScene->Draw();

	ScreenFunction::Draw();
}

void SceneManager::ChangeScene(bool trriger, Scene* next)
{
	if (trriger && ScreenFunction::CheckBlendMin()) {
		Audio::Play("", false);
		Necessary::SetFadeIOFlag(true);//フェードアウト開始
	}
	if (ScreenFunction::CheckBlendMax()) {
		SetScene(next);
		Necessary::SetFadeIOFlag(false);
	}
}

void SceneManager::SetScene(Scene* nextScene)
{
	MemoryFunction::CheckMem(this->nowScene);
	this->nowScene->Finalize();//現在のシーンの終了処理
	delete this->nowScene;
	//シーンの更新
	this->nowScene = nextScene;
	MemoryFunction::CheckMem(this->nowScene);
	this->nowScene->Initialize();
}
