#include "SceneManager.h"
#include"Necessary.h"
#include"ScreenFunction.h"
#include"MemoryFunc.h"
#include"Audio.h"

std::string SelectMusic::Name;

void SceneManager::Initialize()
{
	ScreenFunction::Initialize();

	this->_nowScene = new TitleScene();//�����V�[���̐ݒ�
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

	ScreenFunction::Update();
}

void SceneManager::Draw()
{
	this->_nowScene->Draw();

	ScreenFunction::Draw();
}

bool SceneManager::ChangeScene(bool trriger, SceneKind nextscene)
{
	if (trriger && ScreenFunction::CheckBlendMin()) {
		Audio::Play(this->_nowScene->GetDecisionSEName(), false);
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
	case SceneKind::MusicSelect:return new MusicSelectScene();
	case SceneKind::Game:		return new GameScene();
	case SceneKind::Result:		return new TitleScene();
	default: throw("�\�����Ȃ��V�[�����������Ă��܂�");
	}
	return nullptr;
}

void SceneManager::SetScene(SceneKind kind)
{
	MemoryFunction::CheckMem(this->_nowScene);
	this->_nowScene->Finalize();//���݂̃V�[���̏I������
	delete this->_nowScene;

	//�V�[���̍X�V
	this->_nowScene = SetNextScene(kind);
	MemoryFunction::CheckMem(this->_nowScene);
	this->_nowScene->Initialize();
}