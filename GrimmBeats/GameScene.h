#pragma once
#include"Scene.h"

class GameScene : public Scene {
	bool _isStart;
public:
	GameScene();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};

namespace Counter {
	extern float _gameCnt;
	extern int _perfectCnt;
	extern int _greatCnt;
	extern int _goodCnt;
	extern int _missCnt;
	extern int _score;
	extern int _comboCnt;
}