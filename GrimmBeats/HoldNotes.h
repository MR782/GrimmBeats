#pragma once
#include"Notes.h"

class HoldNotes : public Notes {
	enum class HoldState {
		Hold,
		Non
	};
	HoldState _state;
	int _holdCnt;
public:
	HoldNotes();
	JudgeResult Judge()override;
};