#pragma once
#include"Scene.h"
#include"Lane.h"
#include"JudgeLine.h"
#include"JudgeButton.h"

class GameScene : public Scene {
	JudgeButton* _judgeButoon;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};

namespace Object {
	extern Lane* lane;
	extern JudgeLine* judgeLine;
}

namespace Counter {
	extern float _gameCnt;
}