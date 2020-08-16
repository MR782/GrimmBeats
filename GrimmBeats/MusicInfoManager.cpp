#include "MusicInfoManager.h"

void MusicInfoManager::AddData(MusicInfo info)
{
	this->musicinfoList.push_back(info);
}

void MusicInfoManager::DeleteData(MusicInfo info)
{
	for (auto itr = this->musicinfoList.begin(); itr != this->musicinfoList.end(); itr++) {
		if ((*itr) == info) {
			this->musicinfoList.erase(itr);
			break;
		}
	}
}

void MusicInfoManager::DeleteAll()
{
	this->musicinfoList.clear();
}

MusicInfo MusicInfoManager::GetInfo(std::string name)
{
	for (auto itr = this->musicinfoList.begin(); itr != this->musicinfoList.end(); itr++) {
		if ((*itr).name == name) return (*itr);
	}
	throw("指定された楽曲情報が見つかりませんでした");
}

std::string MusicInfoManager::GetTxtFile(std::string name, Level level)
{
	for (auto itr = this->musicinfoList.begin(); itr != this->musicinfoList.end(); itr++) {
		//名前が一致しないならもう一度探索
		if ((*itr).name != name) continue;
		//txtファイルから指定難易度のファイルを探す
		for (auto itr2 = (*itr).txtFile.begin(); itr2 != (*itr).txtFile.end(); itr2++) {
			if ((*itr2).first == level) return (*itr2).second;
		}
	}
	throw("指定ファイル(txt)が見つかりませんでした");
}
