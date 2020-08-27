#pragma once
#include"Scene.h"
#include "Animation.h"
#include"ComposerLabel.h"
#include"BPMLabel.h"
#include"MusicNameLabel.h"
#include"MusicListItemButton.h"
#include"MusicSelectCursor.h"
#include"SpeedLabel.h"
#include<memory>

class MusicSelectScene : public Scene {
	BPMLabel* bpmLabel;
	MusicNameLabel* musicNameLabel;
	ComposerLabel* composerLabel;
	MusicSelectCursor* cursor;
	SpeedLabel* speedLabel;

	std::unique_ptr<Animation> uiBoard;
public:
	MusicSelectScene();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};

namespace MusicName {
	extern std::string musicName;
}

namespace UIModel {
	extern MusicListItemButton* musicItemList;
}