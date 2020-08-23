#include "ModeSelectCursor.h"
#include"KeyBoard.h"
#include"ModeSelectScene.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"

void ModeSelectCursor::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("ModeSelectCursor");

	this->_nextScene = NextScene::MusicSelect;
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
	if (KeyBoard::KeyDown(KEY_INPUT_UP)) {
		this->_nextScene = (NextScene)(((int)this->_nextScene + 1) % SceneNum);
		Audio::Play("cursor_ModeSelect");
	}
	else if (KeyBoard::KeyDown(KEY_INPUT_DOWN)) {
		this->_nextScene = (NextScene)(((int)this->_nextScene + (SceneNum - 1) % SceneNum));
		Audio::Play("cursor_ModeSelect");
	}
	this->SetPosition();
	#pragma endregion
}

void ModeSelectCursor::Draw()
{
	Rect draw = Rect();
	this->_anim->ExtendAnimeDraw(this->_draw);
}

ModeSelectCursor::NextScene ModeSelectCursor::GetNextScene()
{
	return this->_nextScene;
}

void ModeSelectCursor::SetPosition()
{
	switch (this->_nextScene)
	{
	case ModeSelectCursor::NextScene::MusicSelect:
		this->_draw = ModeSelectUI::gameplay_button->GetDrawRect();
		break;
	case ModeSelectCursor::NextScene::MusicPlayer:
		this->_draw = ModeSelectUI::musicplay_button->GetDrawRect();
		break;
	}
}