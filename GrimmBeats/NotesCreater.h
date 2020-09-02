#pragma once
#include"Notes.h"

class NotesCreater {
	enum class NotesKind {
		Tap = 1,
		Hold = 2
	};
	static std::vector<Notes*> _notesList;

	static NotesKind IdentificationNotes(int kind);
	static Notes* Create(NotesKind kind);
public:
	static void Initialize();
	static void Finalize();

	static std::vector<Notes*> GetNotesList();
};