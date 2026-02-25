#include "gui.h"

GUI::GUI(ServActivitati& s) :serv{s}
{
	asamblareFereastra();
	connect();
	loadData();
}

void GUI::asamblareFereastra()
{
	QHBoxLayout* main_ly = new QHBoxLayout{}, * ly_h1 = new QHBoxLayout{};
	QVBoxLayout* ly_v0 = new QVBoxLayout{}, *ly_v1 = new QVBoxLayout{}, *ly_v2 = new QVBoxLayout{}, *ly_v3 = new QVBoxLayout{};
	QFormLayout* form_ly = new QFormLayout{};
	main_ly->addLayout(ly_v0);
	main_ly->addLayout(ly_v1); 
	main_ly->addLayout(ly_v2);
	main_ly->addLayout(ly_v3);
	ly_v0->addWidget(data2);
	ly_v1->addWidget(data);
	ly_v1->addLayout(ly_h1);
	ly_h1->addWidget(b_all);
	ly_h1->addWidget(b_sort);
	ly_h1->addWidget(b_filter);
	form_ly->addRow("Titlu",titlu); 
	form_ly->addRow("Tip",tip);
	form_ly->addRow("Durata",durata);
	form_ly->addRow("Descriere",descriere);
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
	setLayout(main_ly);
}

void GUI::connect()
{
	QObject::connect(b_curente, &QPushButton::clicked, [&]() {
		GUI_ActCurente* window = new GUI_ActCurente{serv};
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
			serv.adaugare_activitate(tit,desc,tp,nr_dr);
			loadData();
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this,"Warning",QString::fromStdString(error.what()));
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
			loadData();
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this,"Warning",QString::fromStdString(error.what()));
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
			serv.modificare_activitate(tit,desc,tp,nr_dr);
			loadData();
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
			QMessageBox::warning(this,"Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_undo, &QPushButton::clicked, [&]() {
		try
		{
			serv.do_undo();
			loadData();
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(data, &QListWidget::itemSelectionChanged, [&]() {
		auto items = data->selectedItems();
		if (items.isEmpty())
		{
			titlu->setText("");
			tip->setText("");
			durata->setText("");
			descriere->setText("");
		}
		else
		{
			string act_id = items.at(0)->text().toStdString();
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
			data2->clear();
			data->clear(); 
			const vector<Activitate>& acts = serv.sorteaza_activitati();
			int ind = 0;
			for (const auto& act : acts)
			{
				data->addItem(QString::fromStdString(act.get_titlu()));
				int j = ind % nr_coloane, i = (ind - j + 1) / nr_coloane;
				data2->setItem(i, j, new QTableWidgetItem{ QString::fromStdString(act.get_titlu()) });
				ind++;
			}
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_all, &QPushButton::clicked, [&]() {
		try
		{
			loadData();
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
			data2->clear();
			data->clear();
			const vector<Activitate>& acts = serv.filtreaza_dupa_tip(type);
			int ind = 0;
			for (const auto& act : acts)
			{
				data->addItem(QString::fromStdString(act.get_titlu()));
				int j = ind % nr_coloane, i = (ind - j + 1) / nr_coloane;
				data2->setItem(i, j, new QTableWidgetItem{ QString::fromStdString(act.get_titlu()) });
				ind++;
			}
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(data2, &QTableWidget::itemSelectionChanged, [&]() {
		auto items = data2->selectedItems();
		if (items.isEmpty())
		{
			titlu->setText("");
			tip->setText("");
			durata->setText("");
			descriere->setText("");
		}
		else
		{
			string act_id = items.at(0)->text().toStdString();
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
		CosReadOnly* new_window = new CosReadOnly{serv};
		new_window->show();
		});
}

void GUI::loadData()
{
	
	for (auto b : butoane)
		delete b;
	butoane.clear();
	const vector<DTO_Stats>& dtos = serv.raport();
	for (auto elem : dtos)
	{
		auto but = new QPushButton{ QString(elem.key) };
		float nr = elem.sum / elem.nr_obj;
		but->setProperty("nr",nr);
		QObject::connect(but, &QPushButton::clicked, [but,this]() {
			QMessageBox::information(this,"Info",but->property("nr").toString()); 
			});
		butoane.push_back(but);
		ly_but->addWidget(but);
	}

	data2->clear();
	data->clear();
	const vector<Activitate>& acts = serv.obtine_toate_activitatile();
	int ind = 0;
	for (const auto& act : acts)
	{
		data->addItem(QString::fromStdString(act.get_titlu()));
		int j = ind % nr_coloane, i = (ind - j + 1) / nr_coloane;
		data2->setItem(i, j, new QTableWidgetItem{ QString::fromStdString(act.get_titlu()) });
		ind++;
	}
}