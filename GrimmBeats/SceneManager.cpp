#include "SceneManager.h"
#include"Necessary.h"
#include"ScreenFunction.h"
#include"MemoryFunc.h"
#include"Audio.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"ModeSelectScene.h"
#include"MusicSelectScene.h"
#include"MusicPlayerScene.h"

std::string SelectMusic::Name;
Level SelectMusic::level;

void SceneManager::Initialize()
{
	ScreenFunction::Initialize();

	this->_nowScene = new TitleScene();//初期シーンの設定
	this->_nowScene->Initialize();
}

void SceneManager::Finalize()
{
	this->_nowScene->Finalize();

	ScreenFunction::Finalize();

	delete this->_nowScene;
}

void SceneManager::Update()
{
	this->_nowScene->Update();
	if (ScreenFunction::CheckBlendMin() && !this->_actors.empty()) {
		for (auto itr = this->_actors.begin(); itr != this->_actors.end(); itr++) {
			(*itr)->Update();
		}
	}
	ScreenFunction::Update();
}

void SceneManager::Draw()
{
	this->_nowScene->Draw();
	if (!this->_actors.empty()) {
		for (auto itr = this->_actors.begin(); itr != this->_actors.end(); itr++) {
			(*itr)->Draw();
		}
	}
	ScreenFunction::Draw();
}

bool SceneManager::ChangeScene(bool trriger, SceneKind nextscene)
{
	if (trriger && ScreenFunction::CheckBlendMin()) {
		Audio::Play(this->_nowScene->GetDecisionSEName(), false);
		Necessary::SetFadeIOFlag(true);//フェードアウト開始
	}
	if (ScreenFunction::CheckBlendMax()) {
		SetScene(nextscene);
		Necessary::SetFadeIOFlag(false);
		return true;
	}
	return false;
}

void SceneManager::AddActor(GameObject* actor)
{
	MemoryFunction::CheckMem(&actor);
	actor->Initialize();
	this->_actors.push_back(std::move(actor));
}

GameObject* SceneManager::FindActor(std::string name)
{
	for (auto itr = this->_actors.begin(); itr != this->_actors.end(); itr++) {
		if ((*itr)->GetName() != name) continue;
		return (*itr);
	}
	throw("指定されたゲームオブジェクトが見つかりませんでした");
}

void SceneManager::KillActor(std::string name)
{
	for (auto itr = this->_actors.begin(); itr != this->_actors.end(); itr++) {
		if ((*itr)->GetName() != name) continue;
		(*itr)->Finalize();
		delete (*itr);
		this->_actors.erase(itr);
		return;
	}
	throw("指定されたゲームオブジェクトが見つかりませんでした");
}

void SceneManager::KillActorALL()
{
	for (auto itr = this->_actors.begin(); itr != this->_actors.end(); itr++) {
		(*itr)->Finalize();
		delete (*itr);
	}
	this->_actors.clear();
}

Scene* SceneManager::SetNextScene(SceneKind kind)
{
	switch (kind)
	{
	case SceneKind::Title:		return new TitleScene();
	case SceneKind::ModeSelect: return new ModeSelectScene();
	case SceneKind::MusicSelect:return new MusicSelectScene();
	case SceneKind::MusicPlayer: return new MusicPlayerScene();
	case SceneKind::Game:		return new GameScene();
	case SceneKind::Result:		return new TitleScene();
	default: throw("予期しないシーンが代入されています");
	}
	return nullptr;
}

void SceneManager::SetScene(SceneKind kind)
{
	MemoryFunction::CheckMem(this->_nowScene);
	this->_nowScene->Finalize();//現在のシーンの終了処理
	delete this->_nowScene;

	//シーンの更新
	this->_nowScene = SetNextScene(kind);
	MemoryFunction::CheckMem(this->_nowScene);
	this->_nowScene->Initialize();
}