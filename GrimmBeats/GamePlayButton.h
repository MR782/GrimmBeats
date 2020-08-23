#pragma once
#include"GameObject.h"

class GamePlayerButton : public GameObject {
	Rect _drawRect;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;

	Rect GetDrawRect();
};