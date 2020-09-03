#pragma once
#include"GameObject.h"
#include"Necessary.h"
#include"Lane.h"

class Notes : public GameObject {
	void Move();
protected:
	float _holdTime;
	Rect _drawRect;
	LaneName _lane;
	float _perfectTiming;

	bool _judgeFinish;//îªíËÇ™èIóπÇµÇΩÇ©Ç«Ç§Ç©
public:
	void Initialize()final;
	void Finalize()final;
	void Update()final;
	void Draw()final;
	LaneName GetLane();
	void SetInfo(float p_timing, LaneName lane, float holdtime);
	bool GetJudgeFinish();

	virtual JudgeResult Judge() = 0;
};