#pragma once
#include"GameObject.h"

class ModeSelectCursor : public GameObject {
public:
	enum class NextScene {
		MusicSelect = 0,
		MusicPlayer = 1
	};
private:
	NextScene _nextScene;
	Rect _draw;
	void SetPosition();
	void CursorMove(int,NextScene);
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
	
	NextScene GetNextScene();
};