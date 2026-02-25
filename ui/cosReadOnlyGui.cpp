#include "cosReadOnlyGui.h"
#include "utilitati.h"

void CosReadOnly::paintEvent(QPaintEvent* pe)
{
	QPainter p{this};
	int nr_figuri = serv.obtine_activitatile_curente().size();
	for (int k = 0; k < nr_figuri; k++)
	{
		int nr1 = Utils::rand_numar(), nr2 = Utils::rand_numar(), ind = k%2;
		QRect rect{nr1*width()/1000,nr2*height()/1000,ims[ind].width() / 16,ims[ind].height() / 16};
		p.drawImage(rect,ims[ind]);
	}
}

void CosReadOnly::update()
{
	repaint();
}