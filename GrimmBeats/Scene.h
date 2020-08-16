#pragma once
#include"Purpose.h"
#include <map>
#include <string>

class Scene {
	std::map<std::string, Point> _bgPosition;
protected:
	bool _move_background;//�w�i�𓮂�����
	int _background_graph;//�w�i�摜
	//�w�i�`��
	void DrawBG();
public:
	virtual void Initialize();
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw();
};