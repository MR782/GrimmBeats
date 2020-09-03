#pragma once
#include"GameObject.h"
#include "BasicUI.h"

class ScoreLabel : public GameObject {
	Text* _socreLabel;
public:
	ScoreLabel();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};