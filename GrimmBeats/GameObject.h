#pragma once
#include"Purpose.h"
#include"Animation.h"

class GameObject {
protected:
	std::unique_ptr<Animation> _anim;
	Vector2 _position;
public:
    virtual ~GameObject();
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw();

	Vector2 GetPosition();
};