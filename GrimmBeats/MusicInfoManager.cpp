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
	throw("�w�肳�ꂽ�y�ȏ�񂪌�����܂���ł���");
}

std::string MusicInfoManager::GetTxtFile(std::string name, Level level)
{
	for (auto itr = this->musicinfoList.begin(); itr != this->musicinfoList.end(); itr++) {
		//���O����v���Ȃ��Ȃ������x�T��
		if ((*itr).name != name) continue;
		//txt�t�@�C������w���Փx�̃t�@�C����T��
		for (auto itr2 = (*itr).txtFile.begin(); itr2 != (*itr).txtFile.end(); itr2++) {
			if ((*itr2).first == level) return (*itr2).second;
		}
	}
	throw("�w��t�@�C��(txt)��������܂���ł���");
}
