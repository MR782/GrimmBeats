#pragma once
#include"Scene.h"
#include"Lane.h"

class GameScene : public Scene {
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};

namespace Object {
	extern Lane* lane;
}

namespace Counter {
	extern float _gameCnt;
}