#pragma once
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <string>
#include "service_activitati.h"
#include "observer.h"
using std::string;

class GUI_ActCurente : public QWidget, public Observer
{
private:
	ServActivitati& serv;
	QListWidget* data = new QListWidget{};
	QPushButton* b_exit = new QPushButton{ "exit" }, * b_add = new QPushButton{ "add curent" }, * b_add_rand = new QPushButton{ "add random" },
		 * b_delete = new QPushButton{ "delete all" }, * b_export = new QPushButton{"export"};
	QLineEdit* titlu = new QLineEdit{}, * tip = new QLineEdit{}, * descriere = new QLineEdit{}, * durata = new QLineEdit{},
		* nr = new QLineEdit{}, * fisier = new QLineEdit{};
public:
	void update() override; 
	GUI_ActCurente(ServActivitati& s);
	void asamblareFereastra();
	void connect();
	void loadData(const vector<Activitate>& acts);
	~GUI_ActCurente()
	{
		serv.removeObserver(this);
	}
};