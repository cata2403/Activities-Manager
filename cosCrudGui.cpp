#include "cosCrudGui.h"

GUI_ActCurente::GUI_ActCurente(ServActivitati& s) :serv{ s }
{
	serv.addObserver(this);
	loadData(serv.obtine_activitatile_curente());
	connect();
	asamblareFereastra();
}

void GUI_ActCurente::asamblareFereastra()
{
	QHBoxLayout* main_ly = new QHBoxLayout{}, * ly_h1 = new QHBoxLayout{};
	QVBoxLayout* ly_v1 = new QVBoxLayout{}, * ly_v2 = new QVBoxLayout{};
	QFormLayout* ly_f1 = new QFormLayout{}, * ly_f2 = new QFormLayout{};
	setLayout(main_ly);
	main_ly->addLayout(ly_v1);
	main_ly->addLayout(ly_v2);
	ly_f1->addRow("Fisier export", fisier);
	ly_f1->addRow("Nr",nr);
	ly_v1->addLayout(ly_f1);
	ly_v1->addWidget(data);
	ly_v1->addLayout(ly_h1);
	ly_h1->addWidget(b_delete);
	ly_h1->addWidget(b_export);
	ly_f2->addRow("Titlu",titlu);
	ly_f2->addRow("Tip",tip);
	ly_f2->addRow("Durata",durata);
	ly_f2->addRow("Descriere",descriere);
	ly_v2->addLayout(ly_f2);
	ly_v2->addWidget(b_add);
	ly_v2->addWidget(b_add_rand);
	ly_v2->addWidget(b_exit);
}

void GUI_ActCurente::connect()
{
	QObject::connect(b_export, &QPushButton::clicked, [&]() {
		string file_exp = fisier->text().toStdString();
		try
		{
			serv.export_activitati_curente(file_exp);
		}
		catch (const exception& error) 
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what())); 
		}
		});
	QObject::connect(b_exit, &QPushButton::clicked, [&]() {
		close();
		});
	QObject::connect(b_add, &QPushButton::clicked, [&]() {
		string info_titlu = titlu->text().toStdString();
		string info_tip = tip->text().toStdString();
		string info_durata = durata->text().toStdString();
		string info_descriere = descriere->text().toStdString();
		try
		{
			int nr = stoi(info_durata);
			serv.adauga_curente(info_titlu,info_descriere,info_tip,nr);
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this,"Warning",QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_add_rand, &QPushButton::clicked, [&]() {
		string st_nr = nr->text().toStdString();
		try
		{
			int r_nr = stoi(st_nr);
			serv.adauga_curente_random(r_nr);
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(b_delete, &QPushButton::clicked, [&]() {
		try
		{
			serv.golire_curente();
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
	QObject::connect(data, &QListWidget::itemSelectionChanged, [&]() {
		string act_id = data->currentItem()->text().toStdString();
		try
		{
			const vector<Activitate>& acts = serv.obtine_activitatile_curente();
			for (const auto& elem : acts)
				if (elem.get_titlu() == act_id)
				{
					titlu->setText(QString::fromStdString(elem.get_titlu()));
					tip->setText(QString::fromStdString(elem.get_tip()));
					durata->setText(QString::fromStdString(to_string(elem.get_durata())));
					descriere->setText(QString::fromStdString(elem.get_descriere()));
					break;
				}
		}
		catch (const exception& error)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(error.what()));
		}
		});
}

void GUI_ActCurente::update()
{
	loadData(serv.obtine_activitatile_curente());
}

void GUI_ActCurente::loadData(const vector<Activitate>& acts)
{
	data->clear();
	for (const auto& act : acts)
		data->addItem(QString::fromStdString(act.get_titlu()));
}