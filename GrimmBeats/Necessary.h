#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>
#include<map>
#include"Scene.h"

//ゲームを通して必要なものの定義

//難易度リスト
enum class Level {
	normal,
	hard,
	extream
};

//楽曲リスト
enum class MusicList {
	Air = 0,
	PROVIDENCECORE = 1,
	/*
	Fancie = 2,
	m3_500 = 2,
	METATRON = 3,
	Dogbite = 4,
	ChartreuseGreen = 5
	*/
};

enum class JudgeResult{
	Perfect,
	Great,
	Good,
	Miss
};

class Necessary {
private:
	static std::map<MusicList, std::string> musicListItem;
	//false : フェードイン　true : フェードアウト
	static bool fade_ioFlag;
public:
	static int speed;//ノーツの移動する速度

	static void Initialize();

	static void DeleteMusicListItem();
	#pragma region Setter/Getter
	//false : フェードイン　true : フェードアウト
	static void SetFadeIOFlag(bool);
	static void AddMusicListItem(MusicList list,std::string name);
	//フェードフラグ
	static bool GetFadeIOFlag();
	static std::string GetMusicListItem(MusicList list);
	static std::map<MusicList, std::string> GetMusicList();
	#pragma endregion
};