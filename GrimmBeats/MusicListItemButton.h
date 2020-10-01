#pragma once
#include"GameObject.h"

class MusicListItemButton : public GameObject {
	struct MusicListItem {
		MusicListItem(std::string name,Rect rect);
		std::string _name;
		std::unique_ptr<Animation> _anime;
		std::string _graphName;
		Rect _rect;
	};
	static std::vector<MusicListItem> _items;

	static void AddItem(std::string name, std::string graphname, Rect rect);
public:
	void Initialize()override;
	void Finalize()override;
	void Update()override;
	void Draw()override;

	static Rect GetRect(std::string);
};