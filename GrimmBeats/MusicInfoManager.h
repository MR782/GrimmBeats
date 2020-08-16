#pragma once
#include"MusicInfo.h"

class MusicInfoManager {
	std::vector<MusicInfo> musicinfoList;
public:
	void AddData(MusicInfo info);
	void DeleteData(MusicInfo info);
	void DeleteAll();

	MusicInfo GetInfo(std::string name);
	std::string GetTxtFile(std::string name, Level level);
};