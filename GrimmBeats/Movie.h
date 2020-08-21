#pragma once
#include"MovieResource.h"

class Movie {
	std::shared_ptr<MovieObject> object;
public:
	Movie();
	void Draw();
	void Set(std::string name);
	void Delete();
};