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
//以下、管理クラスメソッド
//////////////////////////////////////////////////

std::vector<MusicData> MusicDataManager::musicinfoList;

void MusicDataManager::register_audio(MusicData& data)
{
	//まだ読み込んでいないなら
	if (data.exist == false) {
		musicinfoList.push_back(data);
		data.exist = true;
	}
}

void MusicDataManager::Initialize()
{
	json11::Json json = JsonHelper::JsonInitialize("./data/json/musicData.json");
	//-------------------------------------------------------------
	for (auto& item : json["music"].array_items()) {//ファイル内のデータ分繰り返す
		MusicData musicdata;
		musicdata.exist = true;//まだ読み込んでいない
		musicdata.name = item["name"].string_value();//識別子

		for (auto& scope : item["scope"].array_items()) {//読み込む際の識別子
			musicdata.scopes.push_back(scope.string_value());
		}
		musicdata.SetDefault();//値が入っていない場合デフォルト値をセット

		musicinfoList.push_back(musicdata);
	}
}

void MusicDataManager::Finalize()
{
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
