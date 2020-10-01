#pragma once
#include"Purpose.h"
#include"Necessary.h"
#include"GameObject.h"
#include <map>
#include <string>

enum class SceneKind {
	Title,
	ModeSelect,
	MusicSelect,
	MusicPlayer,
	Game,
	Result
};

class Scene {
protected:
	int graph_Xsize;
	std::map<std::string, Point> _bgPosition;
	bool _move_background;//”wŒi‚ğ“®‚©‚·‚©
	int _background_graph;//”wŒi‰æ‘œ
	std::string decisionSEName;//ƒV[ƒ“‚²‚Æ‚ÌŒˆ’è‰¹
	SceneKind nextScene;
	//”wŒi•`‰æ
	void DrawBG();
	void DrawMoveBG();
public:
	Scene();
	virtual void Initialize();
	virtual void Finalize() = 0;
	virtual void Update() = 0;
	virtual void Draw();

	std::string GetDecisionSEName();
};
