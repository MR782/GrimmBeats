#pragma once
#include<iostream>
#include"Purpose.h"
#include<string.h>
#include"./dxlib/DxLib.h"

//UIに必要なものの定義


enum class Color {
	Orange,//薄い赤
	Red,//赤
	Blue,//青
	Green,//緑
	Yellow,//黄色
	Purple,//紫
	Aqua,//水色
	White,//白
	Black,//黒
	Gray//灰色
};

struct Text {
	Text();
	const char* str;//描画する文字
	int text_width;//テキストの長さ
	Point pos;//表示座標
	int font;//フォントハンドル
	int color;//色
	void SetFont(const char* str, Point pos, int font, int color);
	void DeleteFont();
	void DrawFont();
	template<typename T>
	void DrawFormatFont(T data);
	void SetPosition(Point pos);
};

int CreateMyFont(int size,int thick,bool is_anti_alias);

int SetColor(Color color);

template<typename T>
void Text::DrawFormatFont(T data)
{
	DrawFormatStringToHandle(this->pos.x, this->pos.y, this->color, this->font, this->str, data);
}