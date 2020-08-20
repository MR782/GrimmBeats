#include "MusicDataManager.h"
#include"json11.hpp"
#include"JsonHelper.h"

MusicData::MusicData()
{
	this->name = "";
	this->bpm = 0;
	this->composerName = "";
	this->exist = false;
	this->genre = "";
	this->demomusicFileName = "";
	this->jacketFileName = "";
	this->musicFileName = "";
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
	if (this->genre == "")			  this->genre = "NoGenre";
	if (this->demomusicFileName == "")this->demomusicFileName = "non";
	if (this->jacketFileName == "")   this->jacketFileName = "Non";
	if(this->musicFileName == "")	  this->musicFileName = "Non";
	if (this->level.empty() && this->txtFile.empty()) {
		this->level.push_back(Level::easy);
		this->level.push_back(Level::normal);
		this->level.push_back(Level::hard);
		this->txtFile[Level::easy] = "";
		this->txtFile[Level::normal] = "";
		this->txtFile[Level::hard] = "";
	}
}

///////////////////////////////////////////////////
//�ȉ��A�Ǘ��N���X���\�b�h
//////////////////////////////////////////////////

std::vector<MusicData> MusicDataManager::musicinfoList;

void MusicDataManager::register_audio(MusicData& data)
{
	//�܂��ǂݍ���ł��Ȃ��Ȃ�
	if (data.exist == false) {
		musicinfoList.push_back(data);
		data.exist = true;
	}
}

void MusicDataManager::Initialize()
{
	json11::Json json = JsonHelper::JsonInitialize("./data/json/musicData.json");
	//-------------------------------------------------------------
	for (auto& item : json["music"].array_items()) {//�t�@�C�����̃f�[�^���J��Ԃ�
		MusicData musicdata;
		musicdata.exist = true;//�܂��ǂݍ���ł��Ȃ�
		musicdata.name = item["name"].string_value();//���ʎq

		for (auto& scope : item["scope"].array_items()) {//�ǂݍ��ލۂ̎��ʎq
			musicdata.scopes.push_back(scope.string_value());
		}
		musicdata.SetDefault();//�l�������Ă��Ȃ��ꍇ�f�t�H���g�l���Z�b�g

		musicinfoList.push_back(musicdata);
	}
}

void MusicDataManager::Finalize()
{
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
