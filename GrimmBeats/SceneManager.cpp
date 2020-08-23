#include "SceneManager.h"
#include"Necessary.h"
#include"ScreenFunction.h"
#include"MemoryFunc.h"
#include"Audio.h"

void SceneManager::Initialize()
{
	ScreenFunction::Initialize();

	this->nowScene = new TitleScene();//�����V�[���̐ݒ�
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
		Necessary::SetFadeIOFlag(true);//�t�F�[�h�A�E�g�J�n
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
	default: throw("�\�����Ȃ��V�[�����������Ă��܂�");
	}
	return nullptr;
}

void SceneManager::SetScene(SceneKind kind)
{
	MemoryFunction::CheckMem(this->nowScene);
	this->nowScene->Finalize();//���݂̃V�[���̏I������
	delete this->nowScene;

	//�V�[���̍X�V
	this->nowScene = SetNextScene(kind);
	MemoryFunction::CheckMem(this->nowScene);
	this->nowScene->Initialize();
}