#include "MusicNameLabel.h"
#include"MusicDataManager.h"
#include"MusicSelectScene.h"
#include"ScreenSystem.h"

void MusicNameLabel::Initialize()
{
	this->text = new Text();
	this->text->SetFont("%s", Point(ScreenData::width / 30, ScreenData::height / 20), CreateMyFont((ScreenData::height / 10), 32, false), SetColor(Color::Black));
}

void MusicNameLabel::Finalize()
{
	this->text->DeleteFont();
	delete this->text;
}

void MusicNameLabel::Update()
{
}

void MusicNameLabel::Draw()
{
	this->text->DrawFormatFont(MusicDataManager::GetInfo(MusicName::musicName).name.c_str());
}
