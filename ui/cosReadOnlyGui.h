#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPainter>
#include "observer.h"
#include "service_activitati.h"

class CosReadOnly: public QWidget, public Observer
{
private:
	ServActivitati& serv;
	QList<QImage> ims{ QImage{"carne.jpg"}, QImage{"melc.png"}};
public:
	void paintEvent(QPaintEvent* pe) override;
	CosReadOnly(ServActivitati& s) : serv{ s } {
		serv.addObserver(this);
	};
	void update() override;
	~CosReadOnly()
	{
		serv.removeObserver(this);
	}
};