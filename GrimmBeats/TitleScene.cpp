#include "TitleScene.h"
#include"GraphicResource.h"
#include"ScreenSystem.h"
#include"ScreenFunction.h"
#include"SceneManager.h"
#include"KeyBoard.h"
#include"MemoryFunc.h"
#include"./dxlib/DxLib.h"

void TitleScene::Initialize()
{
	//���\�[�X�̃��[�h
	MovieResource::Load("title");
	//������
	#pragma region �w�i�̏�����
	this->_move_background = false;
	this->_background_graph = GraphicResource::GetHandle("TitleBack")[0];
	//���[�r�[�̏�����
	this->_movie = std::make_unique<Movie>();
	this->_movie->Set("Leaf");
	this->graph_Xsize = ScreenData::width;//�w�i�摜�̑傫�����Z�b�g
	#pragma endregion

	#pragma region �I�u�W�F�N�g�̏�����
	//�K�C�h���x���̏�����
	this->_titleGuide = new TitleGuide();
	MemoryFunction::CheckMem(this->_titleGuide);
	this->_titleGuide->Initialize();
	#pragma endregion
	//�w�i�摜�̏����l�Z�b�g
	this->_bgPosition["bg1"] = Point(0, 0);
}

void TitleScene::Finalize()
{
	this->_movie->Delete();
	this->_movie.reset();

	//this->_titleGuide->Finalize();
	delete this->_titleGuide;
}

void TitleScene::Update()
{
	//�t�F�[�hIO�̍Œ��łȂ����
	if (ScreenFunction::CheckBlendMin()) {
		//this->_titleGuide->Update();
	}
	//�V�[���؂�ւ�-----ENTER�������ƃV�[���J��-----------------------------------
	sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), new GameScene());
}

void TitleScene::Draw()
{
	//�w�i�`��
	this->DrawBG();
	//�f���`��
	this->_movie->Draw();

	//�I�u�W�F�N�g�`��
	this->_titleGuide->Draw();
}
