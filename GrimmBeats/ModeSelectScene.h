#pragma once
#include"Scene.h"

class ModeSelectScene : public Scene {
	enum class NextScene {
		MusicSelect,
		MusicPlayer
	};
	NextScene nextScene;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
};