#pragma once
#include"Scene.h"
#include"Movie.h"
#include"GameObject.h"

class SceneManager {
	Scene* _nowScene;
	std::vector<GameObject*> _actors;

	Scene* SetNextScene(SceneKind kind);
	void SetScene(SceneKind nextScene);
public:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	bool ChangeScene(bool trriger, SceneKind nextscene);

	void AddActor(GameObject* actor);
	GameObject* FindActor(std::string name);
	void KillActor(std::string name);
	void KillActorALL();
};

namespace SelectMusic {
	extern std::string Name;
	extern Level level;
};

extern SceneManager* sceneManager;