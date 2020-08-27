#pragma once
#include"GameObject.h"
#include"BasicUI.h"

class ComposerLabel :public GameObject {
	Text* _text;
public:
	ComposerLabel();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};