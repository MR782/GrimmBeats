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
	MovieResource::Load("title");

	this->_move_background = false;
	this->_background_graph = GraphicResource::GetHandle("TitleBack")[0];
	this->movie = std::make_unique<Movie>();
	this->movie->Set("Leaf");
	this->graph_Xsize = ScreenData::width;
	//�w�i�摜�̏����l�Z�b�g
	this->_bgPosition["bg1"] = Point(0, 0);
}

void TitleScene::Finalize()
{
	this->movie->Delete();
	this->movie.reset();
}

void TitleScene::Update()
{
	//�t�F�[�hIO�̍Œ��łȂ����
	if (ScreenFunction::CheckBlendMin()) {
	}
	//�V�[���؂�ւ�-----ENTER�������ƃV�[���@��-----------------------------------
	sceneManager->ChangeScene(KeyBoard::KeyDown(KEY_INPUT_RETURN), new GameScene());
}

void TitleScene::Draw()
{
	this->DrawBG();

	this->movie->Draw();
}
