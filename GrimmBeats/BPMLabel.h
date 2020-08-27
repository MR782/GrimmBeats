#pragma once
#include"GameObject.h"
#include"BasicUI.h"

class BPMLabel :public GameObject {
	Text* _text;
public:
	BPMLabel();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};