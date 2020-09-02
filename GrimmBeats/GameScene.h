#pragma once
#include"Scene.h"
#include"Lane.h"
#include"JudgeLine.h"
#include"JudgeButton.h"
#include"JudgeResultLabel.h"
#include"ClearGauge.h"
#include"ScoreLabel.h"
#include"NotesController.h"

class GameScene : public Scene {
	ScoreLabel* _scoreLabel;
	JudgeButton* _judgeButton;
	ClearGauge* _clearGauge;
	NotesController* _notesController;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};

namespace Object {
	extern Lane* lane;
	extern JudgeLine* judgeLine;
	extern JudgeResultLabel* judgeResultLabel;
}

namespace Counter {
	extern float _gameCnt;
	extern int _perfectCnt;
	extern int _greatCnt;
	extern int _goodCnt;
	extern int _missCnt;
	extern int _score;
}