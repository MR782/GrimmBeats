#include "NotesCreater.h"
#include"SceneManager.h"
#include"MusicDataManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include"TapNotes.h"
#include"HoldNotes.h"

std::vector<std::unique_ptr<Notes>> NotesCreater::_notesList;

NotesCreater::NotesKind NotesCreater::IdentificationNotes(int kind)
{
	return static_cast<NotesKind>(kind);
}

void NotesCreater::Initialize()
{
	std::ifstream file("./data/txt/" + MusicDataManager::GetTxtFile(SelectMusic::Name, SelectMusic::level) + ".txt");
	if (file.fail()) throw("�w�肳�ꂽ���ʃt�@�C����������܂���");

	//���̕���,�ŋ�؂��ăf�[�^�����Ă���
	while (!file.eof()) {
		//�t�@�C���ɏ�����鏇��------------------
		float p_timing = 0;
		int lane = 0;
		int kind = 0;
		float hold_time = 0;
		//csv(txt)����ǂݍ���---------------------
		file >> p_timing >> lane >> kind >> hold_time;
		//�f�[�^�̑��--------------------------------
		std::unique_ptr<Notes> note = std::move(Create(IdentificationNotes(kind)));
		note->SetInfo(p_timing, static_cast<LaneName>(lane), hold_time);
		//�������̏��L����z�񑤂Ɉڂ�
		_notesList.push_back(std::move(note));
	}
	file.close();
}

void NotesCreater::Finalize()
{
	_notesList.clear();
}

std::vector<std::unique_ptr<Notes>> NotesCreater::GetNotesList()
{
	return std::move(_notesList);
}

std::unique_ptr<Notes> NotesCreater::Create(NotesKind kind)
{
	switch (kind)
	{
	case NotesCreater::NotesKind::Tap:
		return std::move(std::make_unique<TapNotes>());
	case NotesCreater::NotesKind::Hold:
		return std::move(std::make_unique<HoldNotes>());
	}
	throw("�m�[�c�������Ɉُ�Ȓl�������Ă��܂��BNotesCreater::Create(NoteKind)");
}