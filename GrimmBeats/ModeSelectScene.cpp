#include "ModeSelectScene.h"
#include"GraphicResource.h"
#include"Audio.h"
#include"ScreenFunction.h"
#include"KeyBoard.h"
#include"SceneManager.h"
#include"GraphicResource.h"
#include"ModeSelectCursor.h"
#include"GamePlayButton.h"
#include"MusicPlayerButton.h"
#include"./dxlib/DxLib.h"

void ModeSelectScene::Initialize()
{
	//���\�[�X�̃��[�h
	Audio::Load("modeselect");
	Audio::Play("ModeSelectBGM", true);
	GraphicResource::Load("modeselect");

	#pragma region �l�̏�����
	this->_bgPosition.clear();
	this->graph_Xsize = 0;
	this->_background_graph = GraphicResource::GetHandle("ModeSelectBack")[0];
	this->_move_background = false;
	this->decisionSEName = "decision_ModeSelect";
	#pragma endregion

	#pragma region �I�u�W�F�N�g�̏�����
	sceneManager->AddActor(new ModeSelectCursor());
	sceneManager->AddActor(new GamePlayerButton());
	sceneManager->AddActor(new MusicPlayerButton());
	#pragma endregion
}

void ModeSelectScene::Finalize()
{
	this->_background_graph = 0;

	Audio::Stop("ModeSelectBGM");
	Audio::DeleteSoundDataScope("modeselect");
	GraphicResource::DeleteGraphScope("modeselect");

	sceneManager->KillActorALL();
}

void ModeSelectScene::Update()
{
	#pragma region �V�[���J�ڏ���
	//�V�[���؂�ւ�-----ENTER�������ƃV�[���J��-----------------------------------
	switch (ModeSelectCursor::GetNextScene())
	{
	case ModeSelectCursor::NextScene::MusicSelect:
		sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), SceneKind::MusicSelect);
		break;
	case ModeSelectCursor::NextScene::MusicPlayer:
		//sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), SceneKind::MusicPlayer);
		break;
	default:
		throw("���̃V�[�����w�肳��Ă��܂���");
	}
	#pragma endregion

}

void ModeSelectScene::Draw()
{
	this->DrawBG();
}
