#pragma once
#include"Necessary.h"
#include <map>

struct MusicData {
	bool exist;//�ǂݍ��ݍς݂����f
	///Json����ǂݍ��ރf�[�^�B--------------------------------------
	std::string name;//�y�Ȗ�
	std::vector<Level> level;//��Փx���X�g
	std::string composerName;//��Ȏ�
	int bpm;//�y�Ȃ�BPM

	std::map<Level, std::string> txtFile;//��Փx���Ƃ̕��ʃf�[�^�t�@�C����
	std::string musicName;//�y�ȃf�[�^�t�@�C����
	std::string demomusicName;//�f���y�ȃf�[�^�t�@�C����

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