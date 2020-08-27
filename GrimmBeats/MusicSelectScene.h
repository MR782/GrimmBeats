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
	BPMLabel* _bpmLabel;
	MusicNameLabel* _musicNameLabel;
	ComposerLabel* _composerLabel;
	MusicSelectCursor* _cursor;
	SpeedLabel* _speedLabel;

	std::unique_ptr<Animation> _uiBoard;
public:
	MusicSelectScene();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};

namespace UIModel {
	extern MusicListItemButton* musicItemList;
}