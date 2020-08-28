#pragma once
#include"Scene.h"
#include"Lane.h"
#include"JudgeLine.h"
#include"JudgeButton.h"
#include"JudgeResultLabel.h"
#include"ClearGauge.h"
#include"ScoreLabel.h"

//‰¼
#include"Notes.h"

class GameScene : public Scene {
	ScoreLabel* _scoreLabel;
	JudgeButton* _judgeButoon;
	ClearGauge* _clearGauge;

	//‰¼
	Notes* _notes;
	Notes* _notes2;
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
}