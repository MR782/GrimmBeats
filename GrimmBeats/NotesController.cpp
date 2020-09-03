#include "NotesController.h"
#include"NotesCreater.h"
#include"TapNotes.h"
#include"GameScene.h"

void NotesController::Initialize()
{
	this->Allocation();
}

void NotesController::Finalize()
{
	DeleteNotesData(LaneName::DLane);
	DeleteNotesData(LaneName::FLane);
	DeleteNotesData(LaneName::JLane);
	DeleteNotesData(LaneName::KLane);
	DeleteNotesData(LaneName::SPACELane);
	for (auto itr = this->_laneNotesList.begin(); itr != this->_laneNotesList.end(); itr++) {
		(*itr).second.clear();
	}
	this->_laneNotesList.clear();
}

void NotesController::Update()
{
	LaneNotesUpdate(LaneName::DLane);
	LaneNotesUpdate(LaneName::FLane);
	LaneNotesUpdate(LaneName::JLane);
	LaneNotesUpdate(LaneName::KLane);
	LaneNotesUpdate(LaneName::SPACELane);
}

void NotesController::Draw()
{
	LaneNotesDraw(LaneName::DLane);
	LaneNotesDraw(LaneName::FLane);
	LaneNotesDraw(LaneName::JLane);
	LaneNotesDraw(LaneName::KLane);
	LaneNotesDraw(LaneName::SPACELane);
}

void NotesController::SetNotesList(LaneName lane, Notes* note)
{
	this->_laneNotesList[lane].push_back(std::move(note));
}

void NotesController::Allocation()
{
	std::vector<Notes*> notesList = NotesCreater::GetNotesList();

	for (auto itr = notesList.begin(); itr != notesList.end(); itr++) {
		SetNotesList((*itr)->GetLane(), (*itr));
	}
}

void NotesController::DeleteNotesData(LaneName lane)
{
	for (auto itr = this->_laneNotesList[lane].begin(); itr != this->_laneNotesList[lane].end(); itr++) {
		delete (*itr);
	}
}

void NotesController::LaneNotesUpdate(LaneName lane)
{
	for (auto itr = this->_laneNotesList[lane].begin(); itr != this->_laneNotesList[lane].end(); itr++) {
		(*itr)->Update();
	}
	if (this->_laneNotesList[lane].empty()) return;
	//先頭ノーツのみ判定
	JudgeResult jr = ((*this->_laneNotesList[lane].begin())->Judge());
	//判定済みなら削除
	if ((*this->_laneNotesList[lane].begin())->GetJudgeFinish()){
		ResultUpdate(jr);
		this->_laneNotesList[lane].erase(this->_laneNotesList[lane].begin());
	}
	
}

void NotesController::LaneNotesDraw(LaneName lane)
{
	for (auto itr = this->_laneNotesList[lane].begin(); itr != this->_laneNotesList[lane].end(); itr++) {
		(*itr)->Draw();
	}
}

void NotesController::ResultUpdate(JudgeResult jr)
{
	//判定結果に基づいてカウントを増加させる
	switch (jr)
	{
	case JudgeResult::Perfect:
		Counter::_perfectCnt++;
		break;
	case JudgeResult::Great:
		Counter::_greatCnt++;
		break;
	case JudgeResult::Good:
		Counter::_goodCnt++;
		break;
	case JudgeResult::Miss:
		Counter::_missCnt++;
		break;
	}
}