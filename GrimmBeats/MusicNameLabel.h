#pragma once
#include"GameObject.h"
#include"BasicUI.h"

class MusicNameLabel :public GameObject {
	Text* _text;
public:
	MusicNameLabel();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};