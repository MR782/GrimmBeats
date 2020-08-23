#pragma once
#include"GameObject.h"

class MusicPlayerButton : public GameObject {
	Rect _drawRect;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;

	Rect GetDrawRect();
};