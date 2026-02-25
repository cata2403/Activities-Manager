#pragma once
#include "repo_activitati.h"
#include <string>
using std::string;

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdaugare : public ActiuneUndo
{
private:
	RepoActivitati& repo;
	const string titlu;
public:
	UndoAdaugare(RepoActivitati& r, const string& s) : repo{ r }, titlu{ s } {};
	void doUndo();
};

class UndoStergere : public ActiuneUndo
{
private:
	RepoActivitati& repo;
	const Activitate act;
public:
	UndoStergere(RepoActivitati& r, const Activitate& a) : repo{ r }, act{ a } {};
	void doUndo();
};

class UndoModificare : public ActiuneUndo
{
private:
	RepoActivitati& repo;
	const Activitate act;
public:
	UndoModificare(RepoActivitati& r, const Activitate& a) : repo{ r }, act{ a } {};
	void doUndo();
};