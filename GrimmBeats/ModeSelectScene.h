#pragma once
#include"Scene.h"
#include"ModeSelectCursor.h"
#include"GamePlayButton.h"
#include"MusicPlayerButton.h"

class ModeSelectScene : public Scene {
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};

namespace ModeSelectUI {
	extern ModeSelectCursor* cursol;
	extern GamePlayerButton* gameplay_button;
	extern MusicPlayerButton* musicplay_button;
}