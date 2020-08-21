#pragma once
#include"Purpose.h"

//マウス入力を受け取る

class Mouse {
	//左クリック用
	static int left_previous;//1フレーム前
	static int left_current;//作業領域
	//右クリック用
	static int right_previous;//1フレーム前
	static int right_current;//作業領域
public:
	static void Initialize();
	static void Update();
	//左クリック用
	static bool LeftClickDown();
	static bool LeftClickUp();
	static bool LeftClickPress();
	static bool LeftClickNotPress();
	//右クリック用
	static bool RightClickDown();
	static bool RightClickUp();
	static bool RightClickPress();
	static bool RightClickNotPress();
};