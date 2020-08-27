#pragma once
#include"Necessary.h"
#include <map>

struct MusicData {
	bool exist;//読み込み済みか判断
	///Jsonから読み込むデータ達--------------------------------------
	std::string name;//楽曲名
	std::vector<Level> level;//難易度リスト
	std::string composerName;//作曲者
	int bpm;//楽曲のBPM

	std::map<Level, std::string> txtFile;//難易度ごとの譜面データファイル名
	std::string musicName;//楽曲データファイル名
	std::string demomusicName;//デモ楽曲データファイル名

	std::vector<std::string> scopes;
	///--------------------------------------------------------------

	MusicData();
	MusicData GetMusicInfo();
	void SetDefault();

	bool operator==(MusicData data) {
		if (this->name != data.name)						 return false;
		if (this->level != data.level)					     return false;
		if (this->composerName != data.composerName)		 return false;
		if (this->bpm != data.bpm)						     return false;
		if (this->musicName != data.musicName)				 return false;
		if (this->demomusicName != data.musicName)			 return false;
		return true;
	}
};

class MusicDataManager {
	static std::vector<MusicData> musicinfoList;
	static void RegisterData(MusicData&);

	static Level ParseEnum(std::string txt);
public:
	static void Initialize();
	static void Finalize();

	static void DeleteData(std::string name);
	static void DeleteAll();

	static MusicData GetInfo(std::string name);
	static std::string GetTxtFile(std::string name, Level level);
};