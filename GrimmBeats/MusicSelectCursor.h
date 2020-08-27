#pragma once
#include"GameObject.h"
#include"Necessary.h"

class MusicSelectCursor : public GameObject {
	std::map<MusicList, std::string> _musiclist;

	MusicList FindMusicItem(std::string);
	void CursorSet(int,MusicList);
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};