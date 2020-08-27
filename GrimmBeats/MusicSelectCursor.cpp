#include "MusicSelectCursor.h"
#include"KeyBoard.h"
#include"MusicSelectScene.h"
#include"MusicDataManager.h"
#include"Audio.h"
#include"./dxlib/DxLib.h"

void MusicSelectCursor::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("MusicSelectCursor");

	Necessary::AddMusicListItem(MusicList::Air, "Air");
	Necessary::AddMusicListItem(MusicList::PROVIDENCECORE, "PROVIDENCE-CORE");

	this->_musiclist = Necessary::GetMusicList();
}

void MusicSelectCursor::Finalize()
{
	this->_anim.reset();
	Necessary::DeleteMusicListItem();
}

void MusicSelectCursor::Update()
{
	#pragma region カーソル操作
	this->CursorSet(KEY_INPUT_UP, (MusicList)(((int)FindMusicItem(MusicName::musicName) + 1) % ((int)this->_musiclist.size())));
	this->CursorSet(KEY_INPUT_DOWN, (MusicList)(((int)FindMusicItem(MusicName::musicName) + (this->_musiclist.size() - 1)) % (this->_musiclist.size())));
	UIModel::musicItemList->GetRect(MusicName::musicName);
	#pragma endregion
}

void MusicSelectCursor::Draw()
{
	Rect draw = UIModel::musicItemList->GetRect(MusicName::musicName);
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
		Audio::StopScope("game");
		MusicName::musicName = this->_musiclist[item];
		Audio::Play("");
		Audio::Play(MusicDataManager::GetInfo(MusicName::musicName).demomusicName,false);
	}
}