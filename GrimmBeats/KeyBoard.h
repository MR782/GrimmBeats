#pragma once
#include<memory>

//キーボード入力を受け取る

class KeyBoard {
public:
	static void Initialize();//初期化
	static void Finalize();//終了処理
	static void Update();//更新処理
	//キー操作
	static bool KeyDown(int);//押された瞬間
	static bool KeyUp(int);//離された瞬間
	static bool KeyPress(int);//押されている間
private:
	KeyBoard();
	static char* current;//キーボード対応
	static char* previous;//1フレーム前の配列を記憶
};