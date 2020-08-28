#pragma once
#include"GameObject.h"
#include"Necessary.h"
#include"Lane.h"

class Notes : public GameObject {
	Rect _drawRect;

	void Move();
protected:
	LaneName _lane;
	float _perfectTiming;
public:
	void Initialize()final;
	void Finalize()final;
	void Update()final;
	void Draw()final;

	virtual JudgeResult Judge() = 0;
	virtual void SetInfo(float p_timing,LaneName lane);
};