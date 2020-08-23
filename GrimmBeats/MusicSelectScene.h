#pragma once
#include"Scene.h"

class MusicSelectScene : public Scene {
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};