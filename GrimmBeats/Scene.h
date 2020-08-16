#pragma once
#include"Purpose.h"
#include <map>
#include <string>

class Scene {
	std::map<std::string, Point> _bgPosition;
protected:
	bool _move_background;//”wŒi‚ð“®‚©‚·‚©
	int _background_graph;//”wŒi‰æ‘œ
	//”wŒi•`‰æ
	void DrawBG();
public:
	virtual void Initialize();
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw();
};