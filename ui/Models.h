#pragma once
#include <QtWidgets/qtableview.h>
#include <vector>
#include "Activitate.h"
using std::vector;

class ModelTabel: public QAbstractTableModel
{
private:
	vector<Activitate> acts;
public:
	ModelTabel(const vector<Activitate>& v) : acts{ v } {};
	
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setActivs(const vector<Activitate> v, const string& actiune);
};