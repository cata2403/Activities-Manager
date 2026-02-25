#include "gui_VM.h"

GUI_VM::GUI_VM(ServActivitati& s) :serv{ s }
{
	tabl->setModel(model);
	lst->setModel(model);
	asamblareFereastra();
	connect();
	loadData(serv.obtine_toate_activitatile(),"modify");
	//loadButoane();
}

void GUI_VM::asamblareFereastra()
{
	QHBoxLayout* main_ly = new QHBoxLayout{}, * ly_h1 = new QHBoxLayout{};
	QVBoxLayout* ly_v0 = new QVBoxLayout{}, * ly_v1 = new QVBoxLayout{}, * ly_v2 = new QVBoxLayout{}, * ly_v3 = new QVBoxLayout{};
	QFormLayout* form_ly = new QFormLayout{};
	main_ly->addLayout(ly_v0);
	main_ly->addLayout(ly_v1);
	main_ly->addLayout(ly_v2);
	main_ly->addLayout(ly_v3);
	ly_h1->addWidget(b_all);
	ly_h1->addWidget(b_sort);
	ly_h1->addWidget(b_filter);
	form_ly->addRow("Titlu", titlu);
	form_ly->addRow("Tip", tip);
	form_ly->addRow("Durata", durata);
	form_ly->addRow("Descriere", descriere);
	ly_v2->addLayout(form_ly);
	ly_v2->addWidget(b_add);
	ly_v2->addWidget(b_delete);
	ly_v2->addWidget(b_search);
	ly_v2->addWidget(b_modify);
	ly_v2->addWidget(b_undo);
	ly_v3->addLayout(ly_but);
	ly_v3->addWidget(b_curente);
	ly_v3->addWidget(b_cos_view);
	ly_v3->addWidget(b_exit);
	ly_v0->addWidget(tabl);
	ly_v1->addWidget(lst);
	ly_v1->addLayout(ly_h1);
	setLayout(main_ly);
}

void GUI_VM::connect()
{
	QObject::connect(b_curente, &QPushButton::clicked, [&]() {
		GUI_ActCurente* window = new GUI_ActCurente{ serv };
		window->show();
		});
	QObject::connect(b_add, &QPushButton::clicked, [&]() {
		string tit = titlu->text().toStdString();
		string tp = tip->text().toStdString();
		string dr = durata->text().toStdString();
		string desc = descriere->text().toStdString();
		try
		{
			int nr_dr = stoi(dr);
			serv.adaugare_activitate(tit, desc, tp, nr_dr);
			loadData(serv.obtine_toate_activitatile(),"modify");
			//loadButoane();
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_exit, &QPushButton::clicked, [&]() {
		close();
		});
	QObject::connect(b_delete, &QPushButton::clicked, [&]() {
		string act_id = titlu->text().toStdString();
		try
		{
			serv.stergere_activitate(act_id);
			loadData(serv.obtine_toate_activitatile(),"modify");
			//loadButoane();
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_modify, &QPushButton::clicked, [&]() {
		string tit = titlu->text().toStdString();
		string tp = tip->text().toStdString();
		string dr = durata->text().toStdString();
		string desc = descriere->text().toStdString();
		try
		{
			int nr_dr = stoi(dr);
			serv.modificare_activitate(tit, desc, tp, nr_dr);
			loadData(serv.obtine_toate_activitatile(),"modify");
			//loadButoane();
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_search, &QPushButton::clicked, [&]() {
		string act_id = titlu->text().toStdString();
		try
		{
			const Activitate& act = serv.obtine_activitate(act_id);
			tip->setText(QString::fromStdString(act.get_tip()));
			durata->setText(QString::fromStdString(to_string(act.get_durata())));
			descriere->setText(QString::fromStdString(act.get_descriere()));
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_undo, &QPushButton::clicked, [&]() {
		try
		{
			serv.do_undo();
			loadData(serv.obtine_toate_activitatile(),"modify");
			//loadButoane();
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (lst->selectionModel()->selectedIndexes().isEmpty())
		{
			titlu->setText("");
			tip->setText("");
			durata->setText("");
			descriere->setText("");
		}
		else
		{
			auto index = lst->selectionModel()->selectedIndexes().at(0);
			string act_id = index.data(Qt::DisplayRole).toString().toStdString();
			try
			{
				const Activitate& act{ serv.obtine_activitate(act_id) };
				titlu->setText(QString::fromStdString(act.get_titlu()));
				tip->setText(QString::fromStdString(act.get_tip()));
				durata->setText(QString::fromStdString(to_string(act.get_durata())));
				descriere->setText(QString::fromStdString(act.get_descriere()));
			}
			catch (const exception& error)
			{
				QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
			}
		}
		});
	QObject::connect(b_sort, &QPushButton::clicked, [&]() {
		try
		{
			loadData(serv.sorteaza_activitati(),"sort");
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_all, &QPushButton::clicked, [&]() {
		try
		{
			loadData(serv.obtine_toate_activitatile(),"filter");
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_filter, &QPushButton::clicked, [&]() {
		string type = tip->text().toStdString();
		try
		{
			loadData(serv.filtreaza_dupa_tip(type),"filter");
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(tabl->selectionModel(),&QItemSelectionModel::selectionChanged, [&]() {
		if (tabl->selectionModel()->selectedIndexes().isEmpty())
		{
			titlu->setText("");
			tip->setText("");
			durata->setText("");
			descriere->setText("");
		}
		else
		{
			int row = tabl->selectionModel()->selectedIndexes().at(0).row();
			auto cell = tabl->model()->index(row, 0);
			string act_id = tabl->model()->data(cell,Qt::DisplayRole).toString().toStdString();
			try
			{
				const Activitate& act = serv.obtine_activitate(act_id);
				titlu->setText(QString::fromStdString(act.get_titlu()));
				tip->setText(QString::fromStdString(act.get_tip()));
				durata->setText(QString::fromStdString(to_string(act.get_durata())));
				descriere->setText(QString::fromStdString(act.get_descriere()));
			}
			catch (const exception& error)
			{
				QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
			}
		}
		});

	QObject::connect(b_cos_view, &QPushButton::clicked, [&]() {
		CosReadOnly* new_window = new CosReadOnly{ serv };
		new_window->show();
		});
}

void GUI_VM::loadData(const vector<Activitate>& acts, const string& action)
{	
	model->setActivs(acts,action);
}

void GUI_VM::loadButoane()
{
	for (auto b : butoane)
		delete b;
	butoane.clear();
	const vector<DTO_Stats>& dtos = serv.raport();
	for (auto elem : dtos)
	{
		auto but = new QPushButton{ QString(elem.key) };
		float nr = elem.sum / elem.nr_obj;
		but->setProperty("nr", nr);
		QObject::connect(but, &QPushButton::clicked, [but, this]() {
			QMessageBox::information(this, "Info", but->property("nr").toString());
			});
		butoane.push_back(but);
		ly_but->addWidget(but);
	}
}