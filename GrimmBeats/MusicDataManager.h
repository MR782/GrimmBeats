#pragma once
#include"Necessary.h"
#include <map>

struct MusicData {
	bool exist;//�ǂݍ��ݍς݂����f
	std::string name;//�y�Ȗ�
	std::vector<Level> level;//��Փx���X�g
	std::string composerName;//��Ȏ�
	std::string genre;//�y�Ȃ̃W������
	int bpm;//�y�Ȃ�BPM
	std::vector<std::string> scopes;

	std::map<Level, std::string> txtFile;//��Փx���Ƃ̕��ʃf�[�^�t�@�C����
	std::string musicFileName;//�y�ȃf�[�^�t�@�C����
	std::string demomusicFileName;//�f���y�ȃf�[�^�t�@�C����
	std::string jacketFileName;//�W���P�b�g�摜�̃t�@�C����

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