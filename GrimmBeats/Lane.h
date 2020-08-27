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
public:
	virtual ~Lane();
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;

	Rect GetRect(LaneName);
	std::map<LaneName,int> GetKeyCode();
	int GetKeyCode(LaneName);
};