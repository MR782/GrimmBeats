#pragma once
#include"GameObject.h"
#include "BasicUI.h"
#include"Necessary.h"

class JudgeResultLabel : public GameObject {
	std::map<JudgeResult, Text*> _resultText;

	int GetJudgeResultCnt(JudgeResult);
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};