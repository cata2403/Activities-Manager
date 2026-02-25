#include "undo.h"

void UndoAdaugare::doUndo()
{
	repo.stergere(titlu);
}

void UndoStergere::doUndo()
{
	repo.adaugare(act);
}

void UndoModificare::doUndo()
{
	repo.modificare(act);
}