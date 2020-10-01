#pragma once
#include"Notes.h"

class HoldNotes : public Notes {
	enum class HoldState {
		Hold,
		Non
	};
	HoldState _state;
	int _holdCnt;

	void Move()override;
public:
	HoldNotes();
	void Draw()override;

	JudgeResult Judge()override;
	void SetInfo(float p_timing, LaneName lane, float endtime);
};