#pragma once
#include"GameObject.h"
#include"BasicUI.h"

class SpeedLabel :public GameObject {
	Text* text;
	Rect drawRect;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};