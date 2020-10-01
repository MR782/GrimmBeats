#pragma once
#include"GameObject.h"
#include "BasicUI.h"

class ComboLabel : public GameObject {
	Text* _comboLabel;
public:
	ComboLabel();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};