#include "GameScene.h"
#include"GraphicResource.h"

void GameScene::Initialize()
{
	this->_move_background = true;
	this->_background_graph = GraphicResource::get_handle("")[0];
}

void GameScene::Finalize()
{
}

void GameScene::Update()
{
}

void GameScene::Draw()
{
	this->DrawBG();
}
