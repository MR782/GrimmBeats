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
//以下、管理クラスメソッド
//////////////////////////////////////////////////

std::vector<MusicData> MusicDataManager::musicinfoList;

void MusicDataManager::RegisterData(MusicData& data)
{
	//まだ読み込んでいないなら
	if (data.exist == false) {
		musicinfoList.push_back(data);
		data.exist = true;
	}
}

Level MusicDataManager::ParseEnum(std::string txt)
{
	if (txt == "normal") return Level::normal;
	else if (txt == "hard") return Level::hard;
	throw("引数に異常な値が入っています。MusicDataManager : Line.57");
	return Level::normal;
}

void MusicDataManager::Initialize()
{
	json11::Json json = JsonHelper::JsonInitialize("./data/json/musicData.json");
	//-------------------------------------------------------------
	for (auto& item : json["music"].array_items()) {//ファイル内のデータ分繰り返す
		MusicData musicdata;
		musicdata.name = item["name"].string_value();//識別子
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
		for (auto& scope : item["scope"].array_items()) {//読み込む際の識別子
			musicdata.scopes.push_back(scope.string_value());
		}
		musicdata.SetDefault();//値が入っていない場合デフォルト値をセット

		RegisterData(musicdata);
	}
}

void MusicDataManager::Finalize()
{
	musicinfoList.clear();
}

//----------------------------------------------------------------
//以下、楽曲情報の管理クラスメソッド
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
	throw("指定された楽曲情報が見つかりませんでした");
}

std::string MusicDataManager::GetTxtFile(std::string name, Level level)
{
	for (auto itr = musicinfoList.begin(); itr != musicinfoList.end(); itr++) {
		//名前が一致しないならもう一度探索
		if ((*itr).name != name) continue;
		//txtファイルから指定難易度のファイルを探す
		for (auto itr2 = (*itr).txtFile.begin(); itr2 != (*itr).txtFile.end(); itr2++) {
			if ((*itr2).first == level) return (*itr2).second;
		}
	}
	throw("指定ファイル(txt)が見つかりませんでした");
}
