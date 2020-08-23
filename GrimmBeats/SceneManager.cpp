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

bool SceneManager::ChangeScene(bool trriger, SceneKind nextscene)
{
	if (trriger && ScreenFunction::CheckBlendMin()) {
		Audio::Play(this->nowScene->GetDecisionSEName(), false);
		Necessary::SetFadeIOFlag(true);//フェードアウト開始
	}
	if (ScreenFunction::CheckBlendMax()) {
		SetScene(nextscene);
		Necessary::SetFadeIOFlag(false);
		return true;
	}
	return false;
}

Scene* SceneManager::SetNextScene(SceneKind kind)
{
	switch (kind)
	{
	case SceneKind::Title:		return new TitleScene();
	case SceneKind::ModeSelect: return new ModeSelectScene();
	case SceneKind::MusicSelect:return new TitleScene();
	case SceneKind::Game:		return new GameScene();
	case SceneKind::Result:		return new TitleScene();
	default: throw("予期しないシーンが代入されています");
	}
	return nullptr;
}

void SceneManager::SetScene(SceneKind kind)
{
	MemoryFunction::CheckMem(this->nowScene);
	this->nowScene->Finalize();//現在のシーンの終了処理
	delete this->nowScene;

	//シーンの更新
	this->nowScene = SetNextScene(kind);
	MemoryFunction::CheckMem(this->nowScene);
	this->nowScene->Initialize();
}