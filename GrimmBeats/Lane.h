#pragma once
#include"GameObject.h"

enum class LaneName {
	DLane,
	FLane,
	SPACELane,
	JLane,
	KLane,
};

class Lane : public GameObject {
	std::map<LaneName,Rect> _lane;//レーンの描画位置とレーン名
	std::map<LaneName,int> _keycode;//レーンに対応したキーをセット

	bool IsPressed(LaneName);
	void DrawWhiteLane(LaneName);
public:
	virtual ~Lane();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;

	Rect GetRect(LaneName);
	int GetKeyCode(LaneName);
};