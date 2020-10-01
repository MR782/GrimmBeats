#pragma once
#include"GameObject.h"
#include"Necessary.h"

class MusicPlayerCursor : public GameObject {
	std::string _playMusicName;
	bool _loop;
	std::map<MusicList, std::string> _musiclist;

	MusicList FindMusicItem(std::string);
	void CursorSet(int, MusicList);
	void MusicStart();
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};