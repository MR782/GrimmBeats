#pragma once
#include"GameObject.h"
#include"Necessary.h"
#include"Lane.h"

class Notes : public GameObject {
	LaneName _lane;
	float _perfectTiming;
protected:
	JudgeResult Judge();
	void Move();
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};