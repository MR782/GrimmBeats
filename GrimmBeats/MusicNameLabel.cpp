#include "MusicNameLabel.h"
#include"MusicDataManager.h"
#include"SceneManager.h"
#include"ScreenSystem.h"

MusicNameLabel::MusicNameLabel()
{
	this->_text = nullptr;
}

void MusicNameLabel::Initialize()
{
	this->name = "MusciNameLabel";
	this->_text = new Text();
	this->_text->SetFont("%s", Point(ScreenData::width / 30, ScreenData::height / 20), CreateMyFont((ScreenData::height / 10), 32, false), SetColor(Color::Black));
}

void MusicNameLabel::Finalize()
{
	this->_text->DeleteFont();
	delete this->_text;
}

void MusicNameLabel::Update()
{
}

void MusicNameLabel::Draw()
{
	this->_text->DrawFormatFont(MusicDataManager::GetInfo(SelectMusic::Name).name.c_str());
}
