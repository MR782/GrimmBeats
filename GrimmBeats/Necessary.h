#pragma once
#include<iostream>
#include<Windows.h>
#include<vector>

//ゲームを通して必要なものの定義

//シーンリスト
enum class SceneData {
	title,//タイトルシーン
	game,//ゲームシーン
	result,//リザルトシーン
	m_select//楽曲選択シーン
};

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
	static SceneData scene;//シーン
	static MusicList m_list;//楽曲リスト
	//false : フェードイン　true : フェードアウト
	static bool fade_ioFlag;
public:
	static int speed;//ノーツの移動する速度

	static void initialize();

	#pragma region Setter/Getter
	//false : フェードイン　true : フェードアウト
	static void set_fade_ioFlag(bool);
	//シーンのセット
	static void set_scene(SceneData scene_);
	//フェードフラグ
	static bool get_fade_ioFlag();
	#pragma endregion
};