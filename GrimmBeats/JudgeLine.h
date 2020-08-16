#pragma once
#include"GameObject.h"

class JudgeLine : public GameObject {
public:
	virtual ~JudgeLine();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
};