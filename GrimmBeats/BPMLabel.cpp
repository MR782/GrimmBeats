#include "BPMLabel.h"
#include"MusicDataManager.h"
#include"MusicSelectScene.h"
#include"ScreenSystem.h"

void BPMLabel::Initialize()
{
	this->text = new Text();
	this->text->SetFont("BPM : %d", Point(ScreenData::width / 25, ScreenData::height / 3), CreateMyFont((ScreenData::height / 10) - 30, 16, false), SetColor(Color::Black));
}

void BPMLabel::Finalize()
{
	this->text->DeleteFont();
	delete this->text;
}

void BPMLabel::Update()
{
}

void BPMLabel::Draw()
{
	this->text->DrawFormatFont(MusicDataManager::GetInfo(MusicName::musicName).bpm);
}
