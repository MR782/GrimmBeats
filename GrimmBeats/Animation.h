#pragma once
#include <memory>
#include "GraphicResource.h"
#include"Purpose.h"

//アニメーションを行う

class Animation {
private:
	std::shared_ptr<GraphicObject> object;
	int current_anime;//何枚目にいるか
	int current_rate;

	void SwitchAnime();
public:
	Animation();
	~Animation();
	void DrawAnime(Point);
	void DrawAnime(Vector2);
	void ExtendAnimeDraw(Rect);
	void BlinkDraw(int period, int a_percent,Vector2);
	void BlinkExtendDraw(int period, int a_percent, Rect drawrect);
	void Set(std::string);
};