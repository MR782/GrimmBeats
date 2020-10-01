#include "ModeSelectCursor.h"
#include"KeyBoard.h"
#include"ModeSelectScene.h"
#include"Audio.h"
#include"SceneManager.h"
#include"./dxlib/DxLib.h"

ModeSelectCursor::NextScene ModeSelectCursor::_nextScene;

ModeSelectCursor::ModeSelectCursor()
{
	_nextScene = NextScene::MusicSelect;
}

void ModeSelectCursor::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("ModeSelectCursor");

	_nextScene = NextScene::MusicSelect;
	this->_position = Vector2();
	this->_draw = Rect();
}

void ModeSelectCursor::Finalize()
{
	this->_anim.reset();
}

void ModeSelectCursor::Update()
{
	const int SceneNum = 2;
	#pragma region ƒJ[ƒ\ƒ‹‘€ì
	CursorMove(KEY_INPUT_UP, (NextScene)(((int)_nextScene + 1) % SceneNum));
	CursorMove(KEY_INPUT_DOWN, (NextScene)(((int)_nextScene + (SceneNum - 1)) % SceneNum));
	this->SetPosition();
	#pragma endregion
}

void ModeSelectCursor::Draw()
{
	this->_anim->BlinkExtendDraw(200,240,this->_draw);
}

ModeSelectCursor::NextScene ModeSelectCursor::GetNextScene()
{
	return _nextScene;
}

void ModeSelectCursor::SetPosition()
{
	switch (this->_nextScene)
	{
	case ModeSelectCursor::NextScene::MusicSelect:
		this->_draw = sceneManager->FindActor("GamePlayButton")->GetDrawRect();
		break;
	case ModeSelectCursor::NextScene::MusicPlayer:
		this->_draw = sceneManager->FindActor("MusicPlayerButton")->GetDrawRect();
		break;
	}
	this->_draw -= 10;
}

void ModeSelectCursor::CursorMove(int key, NextScene next)
{
	if (KeyBoard::KeyDown(key)) {
		this->_nextScene = next;
		Audio::Play("cursor_ModeSelect");
	}
}
