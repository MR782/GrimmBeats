#pragma once
#include"Movie.h"
#include"Scene.h"

class TitleScene : public Scene {
	std::unique_ptr<Movie> movie;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};