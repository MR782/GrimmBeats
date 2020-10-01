#include "MusicPlayerCursol.h"
#include"SceneManager.h"
#include"KeyBoard.h"
#include"Audio.h"
#include"MusicDataManager.h"
#include"./dxlib/DxLib.h"

void MusicPlayerCursor::Initialize()
{
	this->_anim = std::make_unique<Animation>();
	this->_anim->Set("MusicSelectCursor");

	Necessary::AddMusicListItem(MusicList::Air, "Air");
	Necessary::AddMusicListItem(MusicList::PROVIDENCECORE, "PROVIDENCE-CORE");

	this->_musiclist = Necessary::GetMusicList();
}

void MusicPlayerCursor::Finalize()
{
	this->_anim.reset();
	this->_musiclist.clear();
	Necessary::DeleteMusicListItem();
}

void MusicPlayerCursor::Update()
{
	#pragma region �J�[�\������
	this->CursorSet(KEY_INPUT_UP, (MusicList)(((int)FindMusicItem(SelectMusic::Name) + 1) % ((int)this->_musiclist.size())));
	this->CursorSet(KEY_INPUT_DOWN, (MusicList)(((int)FindMusicItem(SelectMusic::Name) + (this->_musiclist.size() - 1)) % (this->_musiclist.size())));
	//musicItemList->GetRect(SelectMusic::Name);
	#pragma endregion

	#pragma region ���[�v�����ƍĐ�����
	if (KeyBoard::KeyDown(KEY_INPUT_L)) {
		this->_loop = !_loop;
	}
	//Enter�������ꂽ��Ȃ��Z�b�g
	if (KeyBoard::KeyDown(KEY_INPUT_RETURN)) {
		this->_playMusicName =MusicDataManager::GetInfo(SelectMusic::Name).musicName;
		MusicStart();
	}
	//�Đ�����Ă��Ȃ��Ȃ�Đ�(���[�v����)
	if (Audio::CheckPlay(this->_playMusicName) && this->_loop) {
		MusicStart();
	}
	#pragma endregion
}

void MusicPlayerCursor::Draw()
{
	//Rect draw = UIModel::musicItemList->GetRect(SelectMusic::Name);
	//draw -= 10;
	//this->_anim->BlinkExtendDraw(200, 240, draw);
}

MusicList MusicPlayerCursor::FindMusicItem(std::string name)
{
	for (auto itr = _musiclist.begin(); itr != _musiclist.end(); itr++) {
		if (itr->second == name) {
			return itr->first;
			break;
		}
	}
	throw("�w�肳�ꂽ�A�C�e����������܂���ł���");
}

void MusicPlayerCursor::CursorSet(int key, MusicList item)
{
	if (KeyBoard::KeyDown(key)) {
		SelectMusic::Name = this->_musiclist[item];
		Audio::Play("cursor_MusicSelect");
	}
}

void MusicPlayerCursor::MusicStart()
{
	//MusicDataManager::GetInfo(SelectMusic::Name).demomusicName, false
	Audio::Play(this->_playMusicName);
}