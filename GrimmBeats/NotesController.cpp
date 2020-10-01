#include "NotesController.h"
#include"NotesCreater.h"
#include"TapNotes.h"
#include"ClearGauge.h"
#include"GameScene.h"

void NotesController::Initialize()
{
	this->name = "NotesController";
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

void NotesController::SetNotesList(LaneName lane, std::unique_ptr<Notes>& note)
{
	this->_laneNotesList[lane].push_back(std::move(note));
}

void NotesController::Allocation()
{
	std::vector<std::unique_ptr<Notes>> notesList = std::move(NotesCreater::GetNotesList());

	for (auto itr = notesList.begin(); itr != notesList.end(); itr++) {
		SetNotesList((*itr)->GetLane(), (*itr));
	}
}

void NotesController::DeleteNotesData(LaneName lane)
{
	for (auto itr = this->_laneNotesList[lane].begin(); itr != this->_laneNotesList[lane].end(); itr++) {
		itr->reset();
	}
}

void NotesController::LaneNotesUpdate(LaneName lane)
{
	for (auto itr = this->_laneNotesList[lane].begin(); itr != this->_laneNotesList[lane].end(); itr++) {
		(*itr)->Update();
	}
	if (this->_laneNotesList[lane].empty()) return;

	auto item = std::move(this->_laneNotesList[lane].begin());
	//先頭ノーツのみ判定
	JudgeResult jr = (*item)->Judge();
	ResultUpdate(jr);
	if ((*item)->GetJudgeFinish() && jr != JudgeResult::Non) {
		this->_laneNotesList[lane].erase(item);
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
		Counter::_comboCnt++;
		ClearGauge::IncreaseGaugeCnt(3);
		break;
	case JudgeResult::Great:
		Counter::_greatCnt++;
		Counter::_comboCnt++;
		ClearGauge::IncreaseGaugeCnt(2);
		break;
	case JudgeResult::Good:
		Counter::_goodCnt++;
		Counter::_comboCnt++;
		ClearGauge::IncreaseGaugeCnt(1);
		break;
	case JudgeResult::Miss:
		Counter::_missCnt++;
		Counter::_comboCnt = 0;
		ClearGauge::DecreaseGaugeCnt(10);
		break;
	}
}