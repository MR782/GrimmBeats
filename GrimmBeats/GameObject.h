#pragma once
#include"Purpose.h"
#include"Animation.h"

class GameObject {
protected:
	std::string name;
	std::unique_ptr<Animation> _anim;
	Vector2 _position;
	Rect _drawRect;
public:
    virtual ~GameObject();
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw();

	Vector2 GetPosition();
	Rect GetDrawRect();
	std::string GetName();
};