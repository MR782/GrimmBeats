#include "ComposerLabel.h"
#include"MusicDataManager.h"
#include"SceneManager.h"
#include"ScreenSystem.h"

ComposerLabel::ComposerLabel()
{
	this->_text = nullptr;
}

void ComposerLabel::Initialize()
{
	this->name = "ComposerLabel";
	this->_text = new Text();
	this->_text->SetFont("ì‹ÈŽÒ : %s", Point(ScreenData::width / 25, ScreenData::height / 4), CreateMyFont((ScreenData::height / 10) - 30, 16, false), SetColor(Color::Black));
}

void ComposerLabel::Finalize()
{
	this->_text->DeleteFont();
	delete this->_text;
}

void ComposerLabel::Update()
{
}

void ComposerLabel::Draw()
{
	this->_text->DrawFormatFont(MusicDataManager::GetInfo(SelectMusic::Name).composerName.c_str());
}
