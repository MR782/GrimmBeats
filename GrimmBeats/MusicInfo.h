#pragma once
#include"Necessary.h"
#include <map>

struct MusicInfo {
	std::string name;//楽曲名
	std::vector<Level> level;//難易度リスト
	std::string composerName;//作曲者
	std::string genre;//楽曲のジャンル
	int bpm;//楽曲のBPM

	std::map<Level, std::string> txtFile;//難易度ごとの譜面データファイル名
	std::string musicFileName;//楽曲データファイル名
	std::string demomusicFileName;//デモ楽曲データファイル名
	std::string jacketFileName;//ジャケット画像のファイル名

	bool operator==(MusicInfo mi) {
		if (this->name != mi.name)						 return false;
		if (this->level != mi.level)					 return false;
		if (this->composerName != mi.composerName)		 return false;
		if (this->genre != mi.genre)					 return false;
		if (this->bpm != mi.bpm)						 return false;
		if (this->musicFileName != mi.musicFileName)	 return false;
		if (this->demomusicFileName != mi.musicFileName) return false;
		if (this->jacketFileName != mi.jacketFileName)   return false;
		for (auto itr = this->txtFile.begin(); itr != this->txtFile.end(); itr++) {
			if ((*itr).second != this->txtFile.find((*itr).first)->second) return false;
		}
		return true;
	}

	MusicInfo GetMusicInfo();
};