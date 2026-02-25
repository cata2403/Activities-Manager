#pragma once
#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include "service_activitati.h"
#include "cosCrudGui.h"
#include "cosReadOnlyGui.h"
#include "Models.h"

class GUI_VM : public QWidget
{
private:
	ServActivitati& serv;

	QListView* lst = new QListView; 
	QTableView* tabl = new QTableView;
	ModelTabel* model = new ModelTabel{serv.obtine_toate_activitatile()};

	QLineEdit* titlu{ new QLineEdit{} }, * durata{ new QLineEdit{} }, * tip{ new QLineEdit{} }, * descriere{ new QLineEdit{} };
	QPushButton* b_exit = new QPushButton{ "exit" }, * b_add = new QPushButton{ "add" }, * b_delete = new QPushButton{ "delete" },
		* b_search = new QPushButton{ "search" }, * b_modify = new QPushButton{ "modify" }, * b_undo = new QPushButton{ "undo" },
		* b_sort = new QPushButton{ "sort" }, * b_all = new QPushButton{ "all" }, * b_filter = new QPushButton{ "filter by type" },
		* b_curente = new QPushButton{ "[Operatii Cos]" }, * b_cos_view = new QPushButton{ "[Cos read only]" };

	QVBoxLayout* ly_but = new QVBoxLayout{};
	vector<QPushButton*> butoane;

	void loadButoane();
public:
	GUI_VM(ServActivitati& s);
	void asamblareFereastra();
	void connect();
	void loadData(const vector<Activitate>& acts, const string& action);
};