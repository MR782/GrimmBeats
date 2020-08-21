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

MusicList Necessary::m_list;//楽曲

void Necessary::Initialize()
{
	//初期化
	fade_ioFlag = false;
}

void Necessary::SetFadeIOFlag(bool flag)
{
	fade_ioFlag = flag;
}

bool Necessary::GetFadeIOFlag()
{
	return fade_ioFlag;
}

