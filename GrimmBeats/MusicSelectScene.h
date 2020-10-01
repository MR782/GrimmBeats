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
	std::unique_ptr<Animation> _uiBoard;
public:
	MusicSelectScene();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};