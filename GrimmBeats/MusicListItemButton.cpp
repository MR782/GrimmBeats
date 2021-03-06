#include "MusicListItemButton.h"
#include"ScreenSystem.h"

std::vector<MusicListItemButton::MusicListItem> MusicListItemButton::_items;

void MusicListItemButton::AddItem(std::string name, std::string graphname, Rect rect)
{
	MusicListItem item = MusicListItem(name,rect);
	item._anime = std::make_unique<Animation>();
	item._anime->Set(graphname);
	_items.push_back(std::move(item));
}

void MusicListItemButton::Initialize()
{
	this->name = "MusicListItemButton";
	AddItem("Air", "ListItem_Air", Rect(ScreenData::width / 2 + ScreenData::width / 10, ScreenData::height / 5, ScreenData::width / 2 - ScreenData::width / 6, ScreenData::height / 10));
	AddItem("PROVIDENCE-CORE", "ListItem_PROVIDENCE-CORE", Rect(ScreenData::width / 2 + ScreenData::width / 10, ScreenData::height / 5 + ScreenData::height / 5, ScreenData::width / 2 - ScreenData::width / 6, ScreenData::height / 10));
}

void MusicListItemButton::Finalize()
{
	this->_items.clear();
}

void MusicListItemButton::Update()
{
}

void MusicListItemButton::Draw()
{
	for (auto itr = this->_items.begin(); itr != this->_items.end(); itr++) {
		(*itr)._anime->ExtendAnimeDraw((*itr)._rect);
	}
}

Rect MusicListItemButton::GetRect(std::string name)
{
	for (auto itr = _items.begin(); itr != _items.end(); itr++) {
		if ((*itr)._name == name) {
			return (*itr)._rect;
		}
	}
	throw("MusicListItemButtonの矩形が指定された値が取得できませんでした");
}

MusicListItemButton::MusicListItem::MusicListItem(std::string name, Rect rect)
{
	this->_name = name;
	this->_rect = rect;
}
