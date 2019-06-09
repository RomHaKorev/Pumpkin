#include "circulargauge.h"

#include <QDebug>

Pumpkin::CircularGauge::CircularGauge(QWidget *parent) : QWidget(parent),
	renderer(new CircularGaugeRenderer<Pumpkin::CircularGauge>(this))
{
	init();
	resize(120, 120);
	setValue(0);
	setMinimum(0);
	setMaximum(100);
}


void Pumpkin::CircularGauge::paintEvent(QPaintEvent* /*event*/)
{
	QRectF const contentsRect(QRectF(QPointF(0, 0), size()).adjusted(2, 2, -2, -2));
	QPainter painter(this);
	renderer->paint(painter, contentsRect);
}
