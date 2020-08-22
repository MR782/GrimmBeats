#pragma once
#include"Movie.h"
#include"Scene.h"
#include"TitleGuide.h"

class TitleScene : public Scene {
	std::unique_ptr<Movie> _movie;
	TitleGuide* _titleGuide;
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;
};