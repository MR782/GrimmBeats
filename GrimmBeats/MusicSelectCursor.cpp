#include "MusicSelectCursor.h"
#include"KeyBoard.h"
#include"MusicSelectScene.h"
#include"SceneManager.h"
#include"MusicDataManager.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"

void MusicSelectCursor::Initialize()
{
	this->name = "MusicSelectCursor";
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("MusicSelectCursor");

	Necessary::AddMusicListItem(MusicList::Air, "Air");
	Necessary::AddMusicListItem(MusicList::PROVIDENCECORE, "PROVIDENCE-CORE");

	this->_musiclist = Necessary::GetMusicList();
}

void MusicSelectCursor::Finalize()
{
	this->_anim.reset();
	this->_musiclist.clear();
	Necessary::DeleteMusicListItem();
}

void MusicSelectCursor::Update()
{
	#pragma region カーソル操作
	this->CursorSet(KEY_INPUT_UP, (MusicList)(((int)FindMusicItem(SelectMusic::Name) + 1) % ((int)this->_musiclist.size())));
	this->CursorSet(KEY_INPUT_DOWN, (MusicList)(((int)FindMusicItem(SelectMusic::Name) + (this->_musiclist.size() - 1)) % (this->_musiclist.size())));
	MusicListItemButton::GetRect(SelectMusic::Name);
	#pragma endregion
}

void MusicSelectCursor::Draw()
{
	Rect draw = MusicListItemButton::GetRect(SelectMusic::Name);
	draw -= 10;
	this->_anim->BlinkExtendDraw(200,240,draw);
}

MusicList MusicSelectCursor::FindMusicItem(std::string name)
{
	for (auto itr = _musiclist.begin(); itr != _musiclist.end(); itr++) {
		if (itr->second == name) { 
			return itr->first;
			break;
		}
	}
	throw("指定されたアイテムが見つかりませんでした");
}

void MusicSelectCursor::CursorSet(int key, MusicList item)
{
	if (KeyBoard::KeyDown(key)) {
		Audio::StopScope("musicselect");
		SelectMusic::Name = this->_musiclist[item];
		Audio::Play("cursor_MusicSelect");
		Audio::Play(MusicDataManager::GetInfo(SelectMusic::Name).demomusicName, false);
	}
}