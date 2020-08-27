#pragma once
#include"TitleScene.h"
#include"GameScene.h"
#include"ModeSelectScene.h"
#include"MusicSelectScene.h"
#include"Movie.h"

class SceneManager {
	Scene* nowScene;

	Scene* SetNextScene(SceneKind kind);
	void SetScene(SceneKind nextScene);
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	bool ChangeScene(bool trriger, SceneKind nextscene);
};

extern SceneManager* sceneManager;