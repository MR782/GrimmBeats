#include "Necessary.h"
#include"Audio.h"
#include"KeyBoard.h"
#include"./dxlib/DxLib.h"

#include"GameScene.h"
//-------------------------------------
// 実体化
//-------------------------------------
bool Necessary::fade_ioFlag;//フェードを管理するフラグ
int Necessary::speed;//ノーツの落ちる速度

std::map<MusicList, std::string> Necessary::musicListItem;

void Necessary::Initialize()
{
	//初期化
	fade_ioFlag = false;
}

void Necessary::DeleteMusicListItem()
{
	musicListItem.clear();
}

void Necessary::SetFadeIOFlag(bool flag)
{
	fade_ioFlag = flag;
}

void Necessary::AddMusicListItem(MusicList list, std::string name)
{
	musicListItem[list] = name;
}

bool Necessary::GetFadeIOFlag()
{
	return fade_ioFlag;
}

std::string Necessary::GetMusicListItem(MusicList list)
{
	return musicListItem[list];
}

std::map<MusicList, std::string> Necessary::GetMusicList()
{
	return musicListItem;
}


