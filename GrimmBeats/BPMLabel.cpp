#include "BPMLabel.h"
#include"MusicDataManager.h"
#include"SceneManager.h"
#include"ScreenSystem.h"

BPMLabel::BPMLabel()
{
	this->_text = nullptr;
}

void BPMLabel::Initialize()
{
	this->name = "BPMLabel";
	this->_text = new Text();
	this->_text->SetFont("BPM : %d", Point(ScreenData::width / 25, ScreenData::height / 3), CreateMyFont((ScreenData::height / 10) - 30, 16, false), SetColor(Color::Black));
}

void BPMLabel::Finalize()
{
	this->_text->DeleteFont();
	delete this->_text;
}

void BPMLabel::Update()
{
}

void BPMLabel::Draw()
{
	this->_text->DrawFormatFont(MusicDataManager::GetInfo(SelectMusic::Name).bpm);
}
