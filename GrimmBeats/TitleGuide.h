#pragma once
#include"GameObject.h"

class TitleGuide : public GameObject {
public :
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};