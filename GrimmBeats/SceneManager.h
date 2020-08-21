#pragma once
#include"TitleScene.h"
#include"GameScene.h"
#include"Movie.h"

class SceneManager {
	Scene* nowScene;

	void SetScene(Scene* nextScene);
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void ChangeScene(bool trriger, Scene* next);
};

extern SceneManager* sceneManager;