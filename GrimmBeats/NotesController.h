#pragma once
#include"Notes.h"

class NotesController {
	std::map<LaneName, std::vector<Notes*>> _laneNotesList;

	void SetNotesList(LaneName lane,Notes* note);
	void Allocation();
	void DeleteNotesData(LaneName lane);
	void LaneNotesUpdate(LaneName lane);
	void LaneNotesDraw(LaneName lane);
	void ResultUpdate(JudgeResult);
	bool Judged(JudgeResult);
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};