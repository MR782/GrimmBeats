#pragma once
#include"GameObject.h"
#include"BasicUI.h"

class SpeedLabel :public GameObject {
	Text* _text;
	Rect _drawRect;
public:
	SpeedLabel();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};