#pragma once
#include"GameObject.h"

class JudgeButton : public GameObject {
	struct JudgeButtonItem {
		std::string pushGraphName;
		std::string notPushGraphName;
		int key;
		Rect drawRect;
		JudgeButtonItem(std::string, std::string, Rect,int);
		std::unique_ptr<Animation> anime;
	};

	void ButtonGraphChange(JudgeButtonItem&);
	std::vector<JudgeButtonItem> _buttons;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};