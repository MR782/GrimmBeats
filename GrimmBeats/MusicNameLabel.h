#pragma once
#include"GameObject.h"
#include"BasicUI.h"

class MusicNameLabel :public GameObject {
	Text* text;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};