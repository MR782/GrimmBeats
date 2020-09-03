#pragma once
#include"Notes.h"

class NotesCreater {
	enum class NotesKind {
		Tap = 1,
		Hold = 2
	};
	static std::vector<std::unique_ptr<Notes>> _notesList;

	static NotesKind IdentificationNotes(int kind);
	static std::unique_ptr<Notes> Create(NotesKind kind);
public:
	static void Initialize();
	static void Finalize();

	static std::vector<std::unique_ptr<Notes>> GetNotesList();
};