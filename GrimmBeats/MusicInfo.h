#pragma once
#include"Necessary.h"
#include <map>

struct MusicInfo {
	std::string name;//�y�Ȗ�
	std::vector<Level> level;//��Փx���X�g
	std::string composerName;//��Ȏ�
	std::string genre;//�y�Ȃ̃W������
	int bpm;//�y�Ȃ�BPM

	std::map<Level, std::string> txtFile;//��Փx���Ƃ̕��ʃf�[�^�t�@�C����
	std::string musicFileName;//�y�ȃf�[�^�t�@�C����
	std::string demomusicFileName;//�f���y�ȃf�[�^�t�@�C����
	std::string jacketFileName;//�W���P�b�g�摜�̃t�@�C����

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