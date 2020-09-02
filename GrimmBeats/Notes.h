#pragma once
#include"GameObject.h"
#include"Necessary.h"
#include"Lane.h"

class Notes : public GameObject {
	void Move();
	float holdTime;
protected:
	Rect _drawRect;
	LaneName _lane;
	float _perfectTiming;
public:
	void Initialize()final;
	void Finalize()final;
	void Update()final;
	void Draw()final;
	LaneName GetLane();

	virtual JudgeResult Judge() = 0;
	virtual void SetInfo(float p_timing,LaneName lane,float holdtime);
};