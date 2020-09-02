#include "MusicDataManager.h"
#include"json11.hpp"
#include"JsonHelper.h"
#include <iostream>

MusicData::MusicData()
{
	this->name = "";
	this->bpm = 0;
	this->composerName = "";
	this->exist = false;
	this->demomusicName = "";
	this->musicName = "";
	this->level.clear();
	this->txtFile.clear();
}

MusicData MusicData::GetMusicInfo()
{
	return *this;
}

void MusicData::SetDefault()
{
	if (this->name == "")			  this->name = "Default";
	if (this->bpm == 0)				  this->bpm = 100;
	if (this->composerName == "")	  this->composerName = "NoName";
	if (this->demomusicName == "")this->demomusicName = "non";
	if(this->musicName == "")	  this->musicName = "Non";
	if (this->level.empty() && this->txtFile.empty()) {
		this->level.push_back(Level::normal);
		this->level.push_back(Level::hard);
		this->txtFile[Level::normal] = "";
		this->txtFile[Level::hard] = "";
	}
}

///////////////////////////////////////////////////
//�ȉ��A�Ǘ��N���X���\�b�h
//////////////////////////////////////////////////

std::vector<MusicData> MusicDataManager::musicinfoList;

void MusicDataManager::RegisterData(MusicData& data)
{
	//�܂��ǂݍ���ł��Ȃ��Ȃ�
	if (data.exist == false) {
		musicinfoList.push_back(data);
		data.exist = true;
	}
}

Level MusicDataManager::ParseEnum(std::string txt)
{
	if (txt == "normal") return Level::normal;
	else if (txt == "hard") return Level::hard;
	throw("�����Ɉُ�Ȓl�������Ă��܂��BMusicDataManager : Line.57");
	return Level::normal;
}

void MusicDataManager::Initialize()
{
	json11::Json json = JsonHelper::JsonInitialize("./data/json/musicData.json");
	//-------------------------------------------------------------
	for (auto& item : json["music"].array_items()) {//�t�@�C�����̃f�[�^���J��Ԃ�
		MusicData musicdata;
		musicdata.name = item["name"].string_value();//���ʎq
		musicdata.bpm = item["bpm"].int_value();
		musicdata.composerName = item["composer"].string_value();
		musicdata.musicName = item["musicName"].string_value();
		musicdata.demomusicName = item["demomusicName"].string_value();
		for (auto& levelitem : item["level"].array_items()) {
			Level level = MusicDataManager::ParseEnum(levelitem.string_value());
			musicdata.level.push_back(level);
		}
		for (auto& leveltxt : item["levelTxt"].array_items()) {
			for (auto itr = musicdata.level.begin(); itr != musicdata.level.end(); itr++) {
				if (*itr == Level::hard) {
					if (leveltxt.string_value().find("H") != std::string::npos) {
						musicdata.txtFile[*itr] = leveltxt.string_value();
						continue;
					}
				}
				if (*itr == Level::normal) {
					if (leveltxt.string_value().find("N") != std::string::npos) {
						musicdata.txtFile[*itr] = leveltxt.string_value();
						continue;
					}
				}
			}
		}
		for (auto& scope : item["scope"].array_items()) {//�ǂݍ��ލۂ̎��ʎq
			musicdata.scopes.push_back(scope.string_value());
		}
		musicdata.SetDefault();//�l�������Ă��Ȃ��ꍇ�f�t�H���g�l���Z�b�g

		RegisterData(musicdata);
	}
}

void MusicDataManager::Finalize()
{
	musicinfoList.clear();
}

//----------------------------------------------------------------
//�ȉ��A�y�ȏ��̊Ǘ��N���X���\�b�h
//----------------------------------------------------------------
void MusicDataManager::DeleteData(std::string name)
{
	for (auto itr = musicinfoList.begin(); itr != musicinfoList.end(); itr++) {
		if ((*itr).name == name) {
			musicinfoList.erase(itr);
			break;
		}
	}
}

void MusicDataManager::DeleteAll()
{
	musicinfoList.clear();
}

MusicData MusicDataManager::GetInfo(std::string name)
{
	for (auto itr = musicinfoList.begin(); itr != musicinfoList.end(); itr++) {
		if ((*itr).name == name) return (*itr);
	}
	throw("�w�肳�ꂽ�y�ȏ�񂪌�����܂���ł���");
}

std::string MusicDataManager::GetTxtFile(std::string name, Level level)
{
	for (auto itr = musicinfoList.begin(); itr != musicinfoList.end(); itr++) {
		//���O����v���Ȃ��Ȃ������x�T��
		if ((*itr).name != name) continue;
		//txt�t�@�C������w���Փx�̃t�@�C����T��
		for (auto itr2 = (*itr).txtFile.begin(); itr2 != (*itr).txtFile.end(); itr2++) {
			if ((*itr2).first == level) return (*itr2).second;
		}
	}
	throw("�w��t�@�C��(txt)��������܂���ł���");
}
