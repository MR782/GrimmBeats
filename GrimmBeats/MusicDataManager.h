#pragma once
#include"Necessary.h"
#include <map>

struct MusicData {
	bool exist;//読み込み済みか判断
	std::string name;//楽曲名
	std::vector<Level> level;//難易度リスト
	std::string composerName;//作曲者
	std::string genre;//楽曲のジャンル
	int bpm;//楽曲のBPM
	std::vector<std::string> scopes;

	std::map<Level, std::string> txtFile;//難易度ごとの譜面データファイル名
	std::string musicFileName;//楽曲データファイル名
	std::string demomusicFileName;//デモ楽曲データファイル名
	std::string jacketFileName;//ジャケット画像のファイル名

	MusicData();
	MusicData GetMusicInfo();
	void SetDefault();

	bool operator==(MusicData data) {
		if (this->name != data.name)						 return false;
		if (this->level != data.level)					     return false;
		if (this->composerName != data.composerName)		 return false;
		if (this->genre != data.genre)					     return false;
		if (this->bpm != data.bpm)						     return false;
		if (this->musicFileName != data.musicFileName)	     return false;
		if (this->demomusicFileName != data.musicFileName)   return false;
		if (this->jacketFileName != data.jacketFileName)     return false;
		return true;
	}
};

class MusicDataManager {
	static std::vector<MusicData> musicinfoList;
	static void register_audio(MusicData&);
public:
	static void Initialize();
	static void Finalize();

	static void DeleteData(std::string name);
	static void DeleteAll();

	static MusicData GetInfo(std::string name);
	static std::string GetTxtFile(std::string name, Level level);
};