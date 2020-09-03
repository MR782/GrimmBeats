#pragma once
#include"Notes.h"

class NotesController {
	std::map<LaneName, std::vector<std::unique_ptr<Notes>>> _laneNotesList;

	void SetNotesList(LaneName lane,std::unique_ptr<Notes>& note);
	void Allocation();
	void DeleteNotesData(LaneName lane);
	void LaneNotesUpdate(LaneName lane);
	void LaneNotesDraw(LaneName lane);
	void ResultUpdate(JudgeResult);
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};