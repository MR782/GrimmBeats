#pragma once
#include"Notes.h"

class TapNotes : public Notes{
public:
	TapNotes();

	JudgeResult Judge()override;
};