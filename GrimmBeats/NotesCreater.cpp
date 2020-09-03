#include "NotesCreater.h"
#include"SceneManager.h"
#include"MusicDataManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include"TapNotes.h"
#include"HoldNotes.h"

std::vector<Notes*> NotesCreater::_notesList;

NotesCreater::NotesKind NotesCreater::IdentificationNotes(int kind)
{
	return static_cast<NotesKind>(kind);
}

void NotesCreater::Initialize()
{
	std::ifstream file("./data/txt/" + MusicDataManager::GetTxtFile(SelectMusic::Name, SelectMusic::level) + ".txt");
	if (file.fail()) throw("指定された譜面ファイルが見つかりません");

	//この分が,で区切ってデータを入れていく
	while (!file.eof()) {
		//ファイルに書かれる順番------------------
		float p_timing = 0;
		int lane = 0;
		int kind = 0;
		float hold_time = 0;
		//csv(txt)から読み込み---------------------
		file >> p_timing >> lane >> kind >> hold_time;
		//データの代入--------------------------------
		Notes* note = Create(IdentificationNotes(kind));
		note->SetInfo(p_timing, static_cast<LaneName>(lane), hold_time);
		//メモリの所有権を配列側に移す
		_notesList.push_back(std::move(note));
	}
	file.close();
}

void NotesCreater::Finalize()
{
	_notesList.clear();
}

std::vector<Notes*> NotesCreater::GetNotesList()
{
	return _notesList;
}

Notes* NotesCreater::Create(NotesKind kind)
{
	switch (kind)
	{
	case NotesCreater::NotesKind::Tap:
		return new TapNotes();
	case NotesCreater::NotesKind::Hold:
		return new HoldNotes();
	}
	throw("ノーツ生成時に異常な値が入っています。NotesCreater::Create(NoteKind)");
}