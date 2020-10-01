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
	static std::map<LaneName,Rect> _lane;//レーンの描画位置とレーン名
	static std::map<LaneName,int> _keycode;//レーンに対応したキーをセット

	bool IsPressed(LaneName);
	void DrawWhiteLane(LaneName);
public:
	virtual ~Lane();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;

	static Rect GetLaneRect(LaneName);
	static int GetKeyCode(LaneName);
};