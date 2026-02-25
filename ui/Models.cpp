#include "Models.h"

int ModelTabel::rowCount(const QModelIndex&) const
{
	return acts.size();
}

int ModelTabel::columnCount(const QModelIndex&) const
{
	return 3;
}

QVariant ModelTabel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		const Activitate act = acts[index.row()];
		if (index.column() == 0)
			return QString::fromStdString(act.get_titlu());
		if (index.column() == 1)
			return QString::fromStdString(act.get_tip());
		return QString::number(act.get_durata());
	}
	return QVariant{};
}

void ModelTabel::setActivs(const vector<Activitate> v, const string& actiune)
{
		this->acts = v;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
}