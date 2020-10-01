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
	//���\�[�X�̃��[�h
	MovieResource::Load("title");
	Audio::Load("title");
	Audio::Play("TitleBGM", true);
	GraphicResource::Load("title");
	//������
	#pragma region �w�i�̏�����
	this->_move_background = false;
	this->_background_graph = GraphicResource::GetHandle("TitleBack")[0];
	//���[�r�[�̏�����
	this->_movie = std::make_unique<Movie>();
	this->_movie->Set("Leaf");
	this->graph_Xsize = ScreenData::width;//�w�i�摜�̑傫�����Z�b�g
	#pragma endregion

	#pragma region �I�u�W�F�N�g�̐���
	sceneManager->AddActor(new TitleGuide());
	sceneManager->AddActor(new TitleLogo());
	#pragma endregion

	//�����l�Z�b�g
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
	//�V�[���؂�ւ�-----ENTER�������ƃV�[���J��-----------------------------------
	sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN),this->nextScene);
}

void TitleScene::Draw()
{
	//�w�i�`��
	this->DrawBG();
	//�f���`��
	this->_movie->Draw();
}
