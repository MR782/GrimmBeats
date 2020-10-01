#pragma once
#include"GameObject.h"
#include"Necessary.h"
#include"Lane.h"

class Notes : public GameObject {
protected:
	float _holdTime;
	Rect _drawRect;
	LaneName _lane;
	float _perfectTiming;

	bool _judgeFinish;//îªíËÇ™èIóπÇµÇΩÇ©Ç«Ç§Ç©

	virtual void Move();
public:
	Notes();
	void Initialize()final;
	void Finalize()final;
	void Update()final;
	virtual void Draw()override;
	LaneName GetLane();
	virtual void SetInfo(float p_timing, LaneName lane, float holdtime);
	bool GetJudgeFinish();

	virtual JudgeResult Judge() = 0;
};