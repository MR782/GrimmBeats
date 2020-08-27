#include "ComposerLabel.h"
#include"MusicDataManager.h"
#include"MusicSelectScene.h"
#include"ScreenSystem.h"

void ComposerLabel::Initialize()
{
	this->text = new Text();
	this->text->SetFont("ì‹ÈŽÒ : %s", Point(ScreenData::width / 25, ScreenData::height / 4), CreateMyFont((ScreenData::height / 10) - 30, 16, false), SetColor(Color::Black));
}

void ComposerLabel::Finalize()
{
	this->text->DeleteFont();
	delete this->text;
}

void ComposerLabel::Update()
{
}

void ComposerLabel::Draw()
{
	this->text->DrawFormatFont(MusicDataManager::GetInfo(MusicName::musicName).composerName.c_str());
}
