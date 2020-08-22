#include "ModeSelectScene.h"
#include"GraphicResource.h"
#include"Audio.h"
#include"ScreenFunction.h"
#include"KeyBoard.h"
#include"SceneManager.h"
#include"./dxlib/DxLib.h"

void ModeSelectScene::Initialize()
{
	//���\�[�X�̃��[�h
	Audio::Load("modeselect");
	Audio::Play("ModeSelectBGM", true);

	#pragma region �l�̏�����
	this->_bgPosition.clear();
	this->graph_Xsize = 0;
	this->_background_graph = GraphicResource::GetHandle("")[0];
	this->_move_background = false;
	this->nextScene = NextScene::MusicSelect;
	#pragma endregion

	#pragma region �I�u�W�F�N�g�̏�����
	
	#pragma endregion
}

void ModeSelectScene::Finalize()
{
	this->_background_graph = 0;
}

void ModeSelectScene::Update()
{
	//�t�F�[�hIO�̍Œ��łȂ����
	if (ScreenFunction::CheckBlendMin()) {

	}
	
	#pragma region �V�[���J�ڏ���
	//�V�[���؂�ւ�-----ENTER�������ƃV�[���J��-----------------------------------
	switch (this->nextScene)
	{
	case NextScene::MusicSelect:
		sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), SceneKind::MusicSelect);
		break;
	case NextScene::MusicPlayer:
		sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), SceneKind::MusicPlayer);
		break;
	default:
		throw("���̃V�[�����w�肳��Ă��܂���");
	}
	#pragma endregion

}
