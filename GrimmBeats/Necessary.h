#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>
#include"Scene.h"

//ゲームを通して必要なものの定義

//難易度リスト
enum class Level {
	easy,
	normal,
	hard
};

//楽曲リスト
enum class MusicList {
	Air,
	Fancie,
	m3_500,
	METATRON,
	Dogbite,
	ChartreuseGreen,
	PROVIDENCECORE,

	MusicNum
};

class Necessary {
private:
	static MusicList m_list;//楽曲リスト
	//false : フェードイン　true : フェードアウト
	static bool fade_ioFlag;
public:
	static int speed;//ノーツの移動する速度

	static void Initialize();

	#pragma region Setter/Getter
	//false : フェードイン　true : フェードアウト
	static void SetFadeIOFlag(bool);
	//フェードフラグ
	static bool GetFadeIOFlag();
	#pragma endregion
};