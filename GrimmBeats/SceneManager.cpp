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

void SceneManager::ChangeScene(bool trriger, Scene* next)
{
	if (trriger && ScreenFunction::CheckBlendMin()) {
		Audio::Play("", false);
		Necessary::SetFadeIOFlag(true);//�t�F�[�h�A�E�g�J�n
	}
	if (ScreenFunction::CheckBlendMax()) {
		SetScene(next);
		Necessary::SetFadeIOFlag(false);
	}
}

void SceneManager::SetScene(Scene* nextScene)
{
	MemoryFunction::CheckMem(this->nowScene);
	this->nowScene->Finalize();//���݂̃V�[���̏I������
	delete this->nowScene;
	//�V�[���̍X�V
	this->nowScene = nextScene;
	MemoryFunction::CheckMem(this->nowScene);
	this->nowScene->Initialize();
}
